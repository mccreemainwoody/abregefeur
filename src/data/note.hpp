#pragma once

#include <QDateTime>
#include <QUuid>
#include <QtSql/QSqlQuery>

#include <optional>
#include <string>
#include <vector>

namespace abregefeur::data {

    class Note {
       public:
        explicit Note(std::string content);

        static std::vector<Note> find();
        static std::optional<Note> find(const QUuid& id);

        QUuid getId() const;
        std::string getContent() const;
        QDateTime getCreationTimestamp() const;
        std::optional<QDateTime> getUpdateTimestamp() const;
        std::optional<QDateTime> getDeletionTimestamp() const;

        void setContent(std::string content);
        void save();
        void remove();

       private:
        static Note fromDatabase(const QSqlQuery& queryResult);

        Note(QUuid id, std::string content, QDateTime creationTimestamp,
             std::optional<QDateTime> updateTimestamp,
             std::optional<QDateTime> deletionTimestamp);

        void setupQuery(QSqlQuery& query);

        QUuid m_id;
        std::string m_content;
        QDateTime m_creationTimestamp;
        std::optional<QDateTime> m_updateTimestamp;
        std::optional<QDateTime> m_deletionTimestamp;
    };

}  // namespace abregefeur::data
