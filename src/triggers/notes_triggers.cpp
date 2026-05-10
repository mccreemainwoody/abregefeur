#include "notes_triggers.hpp"

#include <QList>
#include <QObject>
#include <QString>

#include <abregefeur/data/note.hpp>
#include <abregefeur/handlers/note_recorder.hpp>
#include "note_view.hpp"

namespace abregefeur::triggers {

    NotesTriggers::NotesTriggers(QObject* parent) : QObject(parent) {}

    NoteView NotesTriggers::toNoteView(const data::Note& note) {
        return NoteView(note.getId(),
                        QString::fromStdString(note.getContent()));
    }

    QList<NoteView> NotesTriggers::getNotes() {
        return noteRecorder_.getNotes() | std::views::transform(toNoteView) |
               std::ranges::to<QList<NoteView>>();
    }

    NoteView NotesTriggers::addNote(const QString& content) {
        const auto note = noteRecorder_.addNote(content.toStdString());

        return toNoteView(note);
    }

}  // namespace abregefeur::triggers
