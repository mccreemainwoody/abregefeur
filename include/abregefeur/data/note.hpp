#pragma once

#include <QDateTime>
#include <QSqlQuery>
#include <QUuid>

#include <optional>
#include <string>

#include <liborm/entity.hpp>

namespace abregefeur::data {

    class Note : public liborm::Entity {
       public:
        static const std::string& getTableName();
        static const std::string& getCols();
        static const std::string& getInsertQuery();
        static const std::string& getUpdateQuery();
        static void setupTable(const QSqlDatabase& database);

        Note(const std::string& content);
        Note(const QSqlQuery& queryResult);

        const std::string& getContent() const;

        void setContent(const std::string& content);

       protected:
        static const std::string tableName_;
        static const std::string cols_;
        static const std::string insertQuery_;
        static const std::string updateQuery_;

        Note(const QUuid& id, const std::string& content,
             const QDateTime& creationTimestamp,
             const std::optional<QDateTime>& updateTimestamp,
             const std::optional<QDateTime>& deletionTimestamp);

        void bindQueryChild(QSqlQuery& query) const;

        std::string content_;
    };

}  // namespace abregefeur::data
