#include "notes_triggers.hpp"

#include <QList>
#include <QString>

#include <note.hpp>

namespace abregefeur::triggers {

    NotesTriggers::NotesTriggers(QObject* parent) : QObject(parent) {}

    NoteView NotesTriggers::toNoteView(const data::Note& note) {
        return NoteView(note.getId(),
                        QString::fromStdString(note.getContent()));
    }

    QList<NoteView> NotesTriggers::getNotes() {
        const auto notes = noteRecorder_.getNotes();
        QList<NoteView> results;
        results.reserve(static_cast<qsizetype>(notes.size()));

        for (const auto& note : notes) {
            results.push_back(toNoteView(note));
        }

        return results;
    }

    NoteView NotesTriggers::addNote(const QString& content) {
        const auto note = noteRecorder_.addNote(content.toStdString());

        return toNoteView(note);
    }

}  // namespace abregefeur::triggers
