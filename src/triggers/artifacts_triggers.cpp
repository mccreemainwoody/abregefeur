#include "artifacts_triggers.hpp"

#include <cstdlib>
#include <libai/providers/openai.hpp>
#include <liborm/repository.hpp>
#include <ranges>
#include <stdexcept>

#include <abregefeur/data/artifact.hpp>
#include <abregefeur/data/artifact_type.hpp>
#include <abregefeur/handlers/artifact_generator.hpp>
#include "artifact_view.hpp"
#include "note_view.hpp"

namespace abregefeur::triggers {

    namespace {
        const std::string extractContent(const NoteView& view) {
            return view.content.toStdString();
        }
    }  // namespace

    ArtifactsTriggers::ArtifactsTriggers(QObject* parent) : QObject(parent) {}

    ArtifactView ArtifactsTriggers::toArtifactView(
        const data::Artifact& artifact) {
        return ArtifactView(artifact.getId(), artifact.getType(),
                            artifact.getPath());
    };

    QList<ArtifactView> ArtifactsTriggers::getArtifacts() const {
        return liborm::repository::find<data::Artifact>() |
               std::views::transform(toArtifactView) |
               std::ranges::to<QList<ArtifactView>>();
    };

    ArtifactView ArtifactsTriggers::generateArtifact(
        const QArtifactType typeInput, const QList<NoteView> notes,
        const QString& extras) const {
        data::ArtifactType type = static_cast<data::ArtifactType>(typeInput);

        const std::vector<std::string> noteStrings =
            notes | std::views::transform(extractContent) |
            std::ranges::to<std::vector<std::string>>();

        // TODO: define proper dependency injection for API key
        const char* api_key_input = std::getenv("OPENAI_API_KEY");

        if (api_key_input == nullptr) {
            throw std::runtime_error(
                "OPENAI_API_KEY is not defined. Please specify an API key "
                "before using the OpenAI backend.");
        }

        const std::string api_key(api_key_input);
        libai::providers::OpenAI provider(api_key);

        const std::string model = "gpt-5";
        handlers::ArtifactGenerator artifactGenerator(provider, model);

        data::Artifact newArtifact = artifactGenerator.generateArtifact(
            type, noteStrings, extras.toStdString());

        return toArtifactView(newArtifact);
    };

}  // namespace abregefeur::triggers
