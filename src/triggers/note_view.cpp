#include "note_view.hpp"

#include <QString>
#include <QUuid>

namespace abregefeur::triggers {

    NoteView::NoteView(QUuid idValue, QString contentValue)
        : id(std::move(idValue)), content(std::move(contentValue)) {}

}  // namespace abregefeur::triggers
