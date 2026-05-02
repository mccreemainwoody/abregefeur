#include "note.hpp"

#include <QTimeZone>
#include <utility>

namespace abregefeur::data {

    namespace {
        QDateTime zeroTimestamp() {
            return QDateTime::fromMSecsSinceEpoch(0, QTimeZone::UTC);
        }
    }  // namespace

    Note::Note(std::string content)
        : m_id(QUuid::createUuid()),
          m_content(std::move(content)),
          m_creationTimestamp(QDateTime::currentDateTimeUtc()),
          m_updateTimestamp(zeroTimestamp()),
          m_deletionTimestamp(zeroTimestamp()) {}

    Note Note::fromDatabase(QUuid id, std::string content,
                            QDateTime creationTimestamp,
                            QDateTime updateTimestamp,
                            QDateTime deletionTimestamp) {
        return Note(std::move(id), std::move(content),
                    std::move(creationTimestamp), std::move(updateTimestamp),
                    std::move(deletionTimestamp));
    }

    QUuid Note::getId() const {
        return m_id;
    }

    std::string Note::getContent() const {
        return m_content;
    }

    QDateTime Note::getCreationTimestamp() const {
        return m_creationTimestamp;
    }

    QDateTime Note::getUpdateTimestamp() const {
        return m_updateTimestamp;
    }

    QDateTime Note::getDeletionTimestamp() const {
        return m_deletionTimestamp;
    }

    void Note::setContent(std::string content) {
        m_content = std::move(content);
    }

    Note::Note(QUuid id, std::string content, QDateTime creationTimestamp,
               QDateTime updateTimestamp, QDateTime deletionTimestamp)
        : m_id(std::move(id)),
          m_content(std::move(content)),
          m_creationTimestamp(std::move(creationTimestamp)),
          m_updateTimestamp(std::move(updateTimestamp)),
          m_deletionTimestamp(std::move(deletionTimestamp)) {}

}  // namespace abregefeur::data
