#include "artifact_view.hpp"

#include <QUuid>
#include <filesystem>

#include <abregefeur/data/artifact_type.hpp>

namespace abregefeur::triggers {

    ArtifactView::ArtifactView(const QUuid& id,
                               const data::ArtifactType artifactType,
                               const std::filesystem::path& path)
        : id(id),
          type(static_cast<QArtifactType>(artifactType)),
          path(path.c_str()) {};

    const std::string ArtifactView::getPath() {
        return path.toStdString();
    }

}  // namespace abregefeur::triggers
