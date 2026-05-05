#include <abregefeur/handlers/note_recorder/note_recorder.hpp>

#include <QUuid>
#include <liborm/repository.hpp>
#include <vector>

#include <abregefeur/data/note.hpp>

namespace abregefeur::handlers {

    namespace repository = liborm::repository;

    std::vector<data::Note> NoteRecorder::getNotes() {
        return repository::find<data::Note>();
    }

    data::Note NoteRecorder::addNote(const std::string& content) {
        data::Note note(content);

        repository::save(note);

        return note;
    }

    void NoteRecorder::removeNote(const QUuid& id) {
        auto note = repository::find<data::Note>(id);

        if (!note) {
            throw new std::invalid_argument(std::format(
                "note with id {} was not found", id.toString().toStdString()));
        }

        repository::remove(*note);
    }

    void NoteRecorder::updateNote(const QUuid& id, const std::string& content) {
        auto note = repository::find<data::Note>(id);

        if (!note) {
            throw new std::invalid_argument(std::format(
                "note with id {} was not found", id.toString().toStdString()));
        }

        note->setContent(content);
        repository::save(*note);
    }

}  // namespace abregefeur::handlers
