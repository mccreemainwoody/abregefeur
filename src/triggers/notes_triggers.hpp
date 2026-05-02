#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include <QtQmlIntegration/QtQmlIntegration>

#include <note.hpp>
#include <note_recorder.hpp>
#include <note_view.hpp>

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
