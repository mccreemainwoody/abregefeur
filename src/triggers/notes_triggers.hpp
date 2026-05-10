#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <QtQmlIntegration/QtQmlIntegration>

#include <abregefeur/data/note.hpp>
#include <abregefeur/handlers/note_recorder.hpp>
#include "note_view.hpp"

namespace abregefeur::triggers {

    class NotesTriggers : public QObject {
        Q_OBJECT
        QML_ELEMENT

       public:
        explicit NotesTriggers(QObject* parent = nullptr);

        Q_INVOKABLE QList<NoteView> getNotes();
        Q_INVOKABLE NoteView addNote(const QString& content);

       private:
        static NoteView toNoteView(const data::Note& note);

        handlers::NoteRecorder noteRecorder_;
    };

}  // namespace abregefeur::triggers
