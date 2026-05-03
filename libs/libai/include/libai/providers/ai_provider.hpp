#pragma once

#include <curl/curl.h>
#include <string>
#include <vector>

#include <libai/utils/http.hpp>

namespace libai::providers {

    class AIProvider {
       public:
        AIProvider(const std::string& name, const std::string& root_url,
                   const std::string& api_key);

        const std::string& getName() const;
        const std::string& getRootUrl() const;
        const std::string& getApiKey() const;
        const int getMaxTokens() const;

        virtual std::vector<std::string> getModels() const = 0;
        virtual const std::string generateSingleResponse(
            const std::string& model_name, const std::string& prompt) const = 0;

       protected:
        virtual utils::http::wrapped_curl_slist getBaseHeaders() const = 0;

        const std::string name_;
        const std::string root_url_;
        const std::string api_key_;
        const int max_tokens_ = 1024;
    };

}  // namespace libai::providers
