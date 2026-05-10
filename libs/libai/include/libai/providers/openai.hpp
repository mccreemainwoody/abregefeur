#pragma once

#include <curl/curl.h>
#include <string>
#include <vector>

#include <libai/providers/ai_provider.hpp>
#include <libai/utils/http.hpp>

namespace libai::providers {

    class OpenAI : public AIProvider {
       public:
        OpenAI(const std::string& api_key);

        std::vector<std::string> getModels() const;
        const std::string generateSingleResponse(
            const std::string& model_name, const std::string& prompt) const;

       protected:
        utils::http::wrapped_curl_slist getBaseHeaders() const;
    };

}  // namespace libai::providers
