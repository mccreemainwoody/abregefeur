#include "note_recorder.hpp"

#include <QUuid>
#include <vector>

#include <note.hpp>

namespace abregefeur::handlers {

    std::vector<data::Note> NoteRecorder::getNotes() {
        return data::Note::find();
    }

    data::Note NoteRecorder::addNote(const std::string& content) {
        data::Note note(content);

        note.save();

        return note;
    }

    void NoteRecorder::removeNote(const QUuid& id) {
        auto note = data::Note::find(id);

        if (!note) {
            throw new std::invalid_argument(std::format(
                "note with id {} was not found", id.toString().toStdString()));
        }

        note->remove();
    }

    void NoteRecorder::updateNote(const QUuid& id, const std::string& content) {
        auto note = data::Note::find(id);

        if (!note) {
            throw new std::invalid_argument(std::format(
                "note with id {} was not found", id.toString().toStdString()));
        }

        note->setContent(content);
        note->save();
    }

}  // namespace abregefeur::handlers
