#pragma once

#include <QObject>
#include <QUuid>
#include <QtQmlIntegration/QtQmlIntegration>
#include <filesystem>

#include <abregefeur/data/artifact_type.hpp>

namespace abregefeur::triggers {

    namespace ArtifactTypeContext {
        Q_NAMESPACE
        QML_NAMED_ELEMENT(ArtifactType)

        enum ArtifactTypeView {
            SUMMARY_MARKDOWN = data::ArtifactType::SUMMARY_MARKDOWN
        };

        Q_ENUM_NS(ArtifactTypeView)
    }  // namespace ArtifactTypeContext

    using QArtifactType = ArtifactTypeContext::ArtifactTypeView;

    class ArtifactView {
        Q_GADGET
        QML_VALUE_TYPE(artifactView)

        Q_PROPERTY(QUuid id MEMBER id)
        Q_PROPERTY(QArtifactType type MEMBER type)
        Q_PROPERTY(QString path MEMBER path)

       public:
        ArtifactView() = default;
        ArtifactView(const QUuid& id, const data::ArtifactType artifactType,
                     const std::filesystem::path& path);

        const std::string getPath();

        QUuid id;
        QArtifactType type;
        QString path;
    };

}  // namespace abregefeur::triggers

Q_DECLARE_METATYPE(abregefeur::triggers::ArtifactView)
