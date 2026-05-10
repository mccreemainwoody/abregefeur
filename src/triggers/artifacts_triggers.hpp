#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <QtQmlIntegration/QtQmlIntegration>

#include <abregefeur/data/artifact.hpp>
#include <abregefeur/data/artifact_type.hpp>
#include <abregefeur/handlers/artifact_generator.hpp>
#include "artifact_view.hpp"
#include "note_view.hpp"

namespace abregefeur::triggers {

    class ArtifactsTriggers : public QObject {
        Q_OBJECT
        QML_ELEMENT

       public:
        explicit ArtifactsTriggers(QObject* parent = nullptr);

        Q_INVOKABLE QList<ArtifactView> getArtifacts() const;
        Q_INVOKABLE ArtifactView
        generateArtifact(const QArtifactType type, const QList<NoteView> notes,
                         const QString& extras = "") const;

       private:
        static ArtifactView toArtifactView(const data::Artifact& artifact);
    };

}  // namespace abregefeur::triggers
