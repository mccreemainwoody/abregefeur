#pragma once

#include <curl/curl.h>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

using nlohmann::json;

namespace libai::utils::http {

    struct CurlSlistDeleter {
        void operator()(curl_slist* slist) const;
    };

    using wrapped_curl_slist = std::unique_ptr<curl_slist, CurlSlistDeleter>;

    wrapped_curl_slist wrap_slist_in_deleter(curl_slist* slist);

    std::string extractTextFromResponsesPayload(const json& payload);

    std::string executeRequest(const std::string& url, curl_slist* headers,
                               const std::string& payload = "",
                               const bool is_get_request = false);

}  // namespace libai::utils::http
