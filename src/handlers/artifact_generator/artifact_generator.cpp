#include <abregefeur/handlers/artifact_generator.hpp>

#include <fstream>
#include <libai/providers/ai_provider.hpp>
#include <liborm/repository.hpp>

#include <abregefeur/data/artifact.hpp>
#include <abregefeur/data/artifact_type.hpp>

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
        const std::string prompt =
            buildArtifactPrompt(artifactType, notes, extras);

        const std::string response =
            provider_.generateSingleResponse(model_name_, prompt);

        const std::filesystem::path artifactPath = "output.md";

        std::ofstream out(artifactPath, std::ios::out | std::ios::trunc);
        out << response;

        data::Artifact artifact(artifactType, artifactPath);

        liborm::repository::save(artifact);

        return artifact;
    }

    const std::string ArtifactGenerator::buildArtifactPrompt(
        const data::ArtifactType artifactType,
        const std::vector<std::string>& notes,
        const std::string& extras) const {
        constexpr std::string_view PROMPT_TEMPLATE =
            ("You are a summarization component inside an application used to "
             "record series of notes written by the end-user and summarizing "
             "them."
             " "
             "Write an organized, concised summary of the following list of "
             "notes, as if you were writing a report or presentation about the "
             "topic(s) mentionned in the notes. The text region containing "
             "notes is presented in the block below (each section on \n\n "
             "within the block represents a new note):."
             "\n\n```\n"
             "{}"
             "\n```\n\n"
             "Your output shall be formatted using the Markdown language. It "
             "is "
             "destined to be converted afterwards to the format {} and will be "
             "made to fit it. Your output will be written using the {} "
             "language."
             "\n\n"
             "Your summary shall be simple to understand and favor "
             "popularization. If technical terms or concepts are to be "
             "presented in your output, remind their meaning. You may use "
             "analogies to make your output simpler to understand."
             "\n\n"
             "You shall also consider the following considerations, specified "
             "by the end user:"
             "\n\n"
             "{}");

        // FIXME: implement a way to change the generation language (config)
        static const std::string language = "English";

        const std::string notes_str =
            notes | std::views::join_with(std::string_view("\n\n")) |
            std::ranges::to<std::string>();

        return std::format(PROMPT_TEMPLATE, notes_str, artifactType, language,
                           extras);
    }

}  // namespace abregefeur::handlers
