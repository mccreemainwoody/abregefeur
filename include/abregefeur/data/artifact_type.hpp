#pragma once

#include <format>
#include <string_view>

namespace abregefeur::data {

    enum ArtifactType {
        SUMMARY_MARKDOWN,
    };

    constexpr const std::string_view get_artifact_type_name(
        const ArtifactType& type) {
        switch (type) {
            case SUMMARY_MARKDOWN:
                return "Markdown";
        }

        throw std::runtime_error("Unreacheable area");
    }

}  // namespace abregefeur::data

template <>
struct std::formatter<abregefeur::data::ArtifactType, char>
    : std::formatter<std::string_view, char> {

    template <class FmtContext>
    auto format(abregefeur::data::ArtifactType type,
                FmtContext& context) const {
        return std::formatter<std::string_view, char>::format(
            abregefeur::data::get_artifact_type_name(type), context);
    };
};
