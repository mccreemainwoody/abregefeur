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
        explicit Note(const std::string& content);

        Note(const Note&) = delete;
        Note(Note&&) noexcept = default;
        Note& operator=(const Note&) = delete;
        Note& operator=(Note&&) = delete;

        static std::vector<Note> find();
        static std::optional<Note> find(const QUuid& id);
        static void setupTable(const QSqlDatabase& database);

        const QUuid& getId() const;
        const std::string& getContent() const;
        const QDateTime& getCreationTimestamp() const;
        const std::optional<QDateTime>& getUpdateTimestamp() const;
        const std::optional<QDateTime>& getDeletionTimestamp() const;

        void setContent(const std::string& content);
        void save();
        void remove();

       private:
        static Note fromDatabase(const QSqlQuery& queryResult);

        Note(const QUuid& id, const std::string& content,
             const QDateTime& creationTimestamp,
             const std::optional<QDateTime>& updateTimestamp,
             const std::optional<QDateTime>& deletionTimestamp);

        void setupQuery(QSqlQuery& query);

        const QUuid m_id;
        std::string m_content;
        const QDateTime m_creationTimestamp;
        std::optional<QDateTime> m_updateTimestamp;
        std::optional<QDateTime> m_deletionTimestamp;
    };

}  // namespace abregefeur::data
