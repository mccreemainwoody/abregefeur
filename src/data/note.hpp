#pragma once

#include <QDateTime>
#include <QUuid>

#include <string>

namespace abregefeur::data {

    class Note {
       public:
        explicit Note(std::string content);

        static Note find(const QUuid& id);

        QUuid getId() const;
        std::string getContent() const;
        QDateTime getCreationTimestamp() const;
        QDateTime getUpdateTimestamp() const;
        QDateTime getDeletionTimestamp() const;

        void setContent(std::string content);
        void save();
        void remove();

       private:
        static Note fromDatabase(QUuid id, std::string content,
                                 QDateTime creationTimestamp,
                                 QDateTime updateTimestamp,
                                 QDateTime deletionTimestamp);

        Note(QUuid id, std::string content, QDateTime creationTimestamp,
             QDateTime updateTimestamp, QDateTime deletionTimestamp);

        QUuid m_id;
        std::string m_content;
        QDateTime m_creationTimestamp;
        QDateTime m_updateTimestamp;
        QDateTime m_deletionTimestamp;
    };

}  // namespace abregefeur::data
