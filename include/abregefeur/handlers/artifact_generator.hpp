#pragma once

#include <libai/providers/ai_provider.hpp>

#include <abregefeur/data/artifact.hpp>
#include <abregefeur/data/artifact_type.hpp>

namespace abregefeur::handlers {

    using libai::providers::AIProvider;

    class ArtifactGenerator {
       public:
        ArtifactGenerator(const AIProvider& provider,
                          const std::string& model_name);

        const AIProvider& getProvider() const;

        const data::Artifact generateArtifact(
            const data::ArtifactType artifactType,
            const std::vector<std::string>& notes,
            const std::string& extras) const;

       private:
        const std::string buildArtifactPrompt(
            const data::ArtifactType artifactType,
            const std::vector<std::string>& notes,
            const std::string& extras) const;

        const AIProvider& provider_;
        const std::string& model_name_;
    };

}  // namespace abregefeur::handlers
