#pragma once

#include <QString>
#include <QUuid>
#include <QtQmlIntegration/QtQmlIntegration>

namespace abregefeur::triggers {

    class NoteView {
        Q_GADGET
        QML_VALUE_TYPE(noteView)

        Q_PROPERTY(QUuid id MEMBER id)
        Q_PROPERTY(QString content MEMBER content)

       public:
        NoteView() = default;
        NoteView(QUuid id, QString content);

        QUuid id;
        QString content;
    };

}  // namespace abregefeur::triggers

Q_DECLARE_METATYPE(abregefeur::triggers::NoteView)
