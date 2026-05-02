#include "note_view.hpp"

#include <utility>

namespace abregefeur::triggers {

    NoteView::NoteView(QUuid idValue, QString contentValue)
        : id(std::move(idValue)), content(std::move(contentValue)) {}

}  // namespace abregefeur::triggers
