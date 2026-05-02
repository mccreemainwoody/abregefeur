#pragma once

#include <QUuid>
#include <vector>

#include <note.hpp>

namespace abregefeur::handlers {

    class NoteRecorder {
       public:
        std::vector<data::Note> getNotes();
        void addNote(const std::string& content);
        void updateNote(const QUuid& id, const std::string& content);
        void removeNote(const QUuid& id);
    };

}  // namespace abregefeur::handlers
