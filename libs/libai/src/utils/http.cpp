#include <libai/utils/http.hpp>

#include <memory>

using nlohmann::json;

namespace libai::utils::http {

    namespace {
        size_t writeResponseCallback(void* contents, size_t size, size_t nmemb,
                                     void* userp) {
            const auto response_chunk_size = size * nmemb;
            auto* response = static_cast<std::string*>(userp);
            response->append(static_cast<char*>(contents), response_chunk_size);
            return response_chunk_size;
        }
    }  // namespace

    void CurlSlistDeleter::operator()(curl_slist* headers) const {
        if (headers == nullptr) {
            return;
        }

        curl_slist_free_all(headers);
    };

    std::unique_ptr<curl_slist, CurlSlistDeleter> wrap_slist_in_deleter(
        curl_slist* slist) {
        std::unique_ptr<curl_slist, CurlSlistDeleter> wrapper(slist);

        return std::move(wrapper);
    }

    std::string extractTextFromResponsesPayload(const json& payload) {
        if (payload.contains("output_text") &&
            payload["output_text"].is_string()) {
            return payload["output_text"].get<std::string>();
        }

        if (!payload.contains("output") || !payload["output"].is_array()) {
            return {};
        }

        for (const auto& output_item : payload["output"]) {
            if (!output_item.contains("content") ||
                !output_item["content"].is_array()) {
                continue;
            }

            for (const auto& content_item : output_item["content"]) {
                if (!content_item.contains("text") ||
                    !content_item["text"].is_string()) {
                    continue;
                }

                return content_item["text"].get<std::string>();
            }
        }

        return {};
    }

    std::string executeRequest(const std::string& url, curl_slist* headers,
                               const std::string& payload,
                               const bool is_get_request) {
        CURL* curl = curl_easy_init();

        if (!curl) {
            throw std::runtime_error(
                std::format("failed to initialize curl for query at {}", url));
        }

        std::string response;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeResponseCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        if (is_get_request) {
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        } else {
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        }

        const CURLcode request_result = curl_easy_perform(curl);
        if (request_result != CURLE_OK) {
            const std::string error_message =
                std::format("request to {} failed: {}", url,
                            std::string(curl_easy_strerror(request_result)));
            curl_easy_cleanup(curl);
            throw std::runtime_error(error_message);
        }

        long status_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);
        curl_easy_cleanup(curl);

        if (status_code < 200 || status_code >= 300) {
            throw std::runtime_error(
                std::format("request to {} failed with status {}: {}", url,
                            status_code, response));
        }

        return response;
    }

}  // namespace libai::utils::http
