#include <abregefeur/handlers/artifact_generator.hpp>

#include <fstream>
#include <libai/providers/ai_provider.hpp>
#include <liborm/repository.hpp>

#include <abregefeur/data/artifact.hpp>

namespace abregefeur::handlers {

    using libai::providers::AIProvider;

    ArtifactGenerator::ArtifactGenerator(const AIProvider& provider,
                                         const std::string& model_name)
        : provider_(std::move(provider)), model_name_(std::move(model_name)) {};

    const AIProvider& ArtifactGenerator::getProvider() const {
        return provider_;
    }

    const data::Artifact ArtifactGenerator::generateArtifact(
        const data::ArtifactType artifactType,
        const std::vector<std::string>& notes,
        const std::string& extras) const {
        // 1. Create the prompt.
        const std::string prompt =
            buildArtifactPrompt(artifactType, notes, extras);

        // 2. Send the prompt to the AI and return the response.
        const std::string response =
            provider_.generateSingleResponse(model_name_, prompt);

        // 3. Build the artifact.
        // 4. Save the artifact at path
        const std::filesystem::path artifactPath = "output.md";

        std::ofstream out(artifactPath, std::ios::out | std::ios::trunc);
        out << response;

        data::Artifact artifact(artifactType, artifactPath);

        liborm::repository::save(artifact);

        return artifact;
    }

}  // namespace abregefeur::handlers
