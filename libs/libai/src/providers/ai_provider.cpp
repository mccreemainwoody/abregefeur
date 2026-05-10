#include <libai/providers/ai_provider.hpp>

#include <string>

namespace libai::providers {

    AIProvider::AIProvider(const std::string& name, const std::string& root_url,
                           const std::string& api_key)
        : name_(name), root_url_(root_url), api_key_(api_key) {};

    const std::string& AIProvider::getApiKey() const {
        return api_key_;
    }

    const int AIProvider::getMaxTokens() const {
        return max_tokens_;
    }

    const std::string& AIProvider::getName() const {
        return name_;
    }

    const std::string& AIProvider::getRootUrl() const {
        return root_url_;
    }

}  // namespace libai::providers
