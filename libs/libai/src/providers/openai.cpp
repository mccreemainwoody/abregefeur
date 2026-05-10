#include <libai/providers/openai.hpp>

#include <curl/curl.h>
#include <format>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include <libai/utils/http.hpp>

using nlohmann::json;

namespace libai::providers {

    OpenAI::OpenAI(const std::string& api_key)
        : AIProvider("OpenAI", "https://api.openai.com/v1", api_key) {};

    utils::http::wrapped_curl_slist OpenAI::getBaseHeaders() const {
        curl_slist* headers = nullptr;

        headers = curl_slist_append(
            headers, std::format("Authorization: Bearer {}", api_key_).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        utils::http::wrapped_curl_slist wrapper =
            utils::http::wrap_slist_in_deleter(headers);

        return std::move(wrapper);
    }

    std::vector<std::string> OpenAI::getModels() const {
        const std::string models_endpoint = std::format("{}/models", root_url_);

        const utils::http::wrapped_curl_slist headers = getBaseHeaders();
        const std::string response = utils::http::executeRequest(
            models_endpoint, headers.get(), "", true);

        const auto payload = json::parse(response);

        if (!payload.contains("data") || !payload["data"].is_array()) {
            throw std::runtime_error(
                std::format("invalid models response payload: {}", response));
        }

        std::vector<std::string> available_models;

        for (const auto& item : payload["data"]) {
            if (!item.contains("id") || !item["id"].is_string()) {
                continue;
            }

            available_models.push_back(item["id"].get<std::string>());
        }

        return std::move(available_models);
    }

    const std::string OpenAI::generateSingleResponse(
        const std::string& model_name, const std::string& prompt) const {
        const auto headers = getBaseHeaders();
        const std::string responses_endpoint =
            std::format("{}/{}", root_url_, "responses");

        const json payload = {
            {"model", model_name},
            {"input", prompt},
            {"max_output_tokens", max_tokens_},
            {"stream", false},
        };

        const std::string response = utils::http::executeRequest(
            responses_endpoint, headers.get(), payload.dump());

        const auto parsed_response = json::parse(response);

        const std::string output_text =
            utils::http::extractTextFromResponsesPayload(parsed_response);

        if (output_text.empty()) {
            throw std::runtime_error(std::format(
                "response payload does not contain text: {}", response));
        }

        return output_text;
    }

}  // namespace libai::providers
