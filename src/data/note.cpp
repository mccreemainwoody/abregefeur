#include <abregefeur/data/note.hpp>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <format>
#include <stdexcept>
#include <string>

#include <abregefeur/data/database.hpp>

namespace abregefeur::data {

    const std::string Note::tableName_ = "notes";
    const std::string Note::cols_ = "content";
    const std::string Note::insertQuery_ =
        "INSERT INTO notes (id, content, creation_timestamp, "
        "update_timestamp, deletion_timestamp) "
        "VALUES (:id, :content, :creation_timestamp, :update_timestamp, "
        ":deletion_timestamp);";
    const std::string Note::updateQuery_ =
        "UPDATE notes "
        "SET content = :content, update_timestamp = :update_timestamp, "
        "deletion_timestamp = :deletion_timestamp "
        "WHERE id = :id;";

    Note::Note(const std::string& content)
        : liborm::Entity(), content_(content) {};

    Note::Note(const QUuid& id, const std::string& content,
               const QDateTime& creationTimestamp,
               const std::optional<QDateTime>& updateTimestamp,
               const std::optional<QDateTime>& deletionTimestamp)
        : liborm::Entity(id, creationTimestamp, updateTimestamp,
                         deletionTimestamp),
          content_(std::move(content)) {};

    Note::Note(const QSqlQuery& queryResult)
        : liborm::Entity(queryResult),
          content_(queryResult.value(4).toString().toStdString()) {};

    const std::string& Note::getTableName() {
        return tableName_;
    }

    const std::string& Note::getCols() {
        return cols_;
    }

    const std::string& Note::getInsertQuery() {
        return insertQuery_;
    }

    const std::string& Note::getUpdateQuery() {
        return updateQuery_;
    }

    const std::string& Note::getContent() const {
        return content_;
    }

    void Note::setContent(const std::string& content) {
        content_ = content;
    }

    void Note::setupTable(const QSqlDatabase& database) {
        QSqlQuery query(database);

        if (!query.exec("CREATE TABLE IF NOT EXISTS notes ("
                        "id TEXT PRIMARY KEY,"
                        "content TEXT NOT NULL,"
                        "creation_timestamp INTEGER NOT NULL,"
                        "update_timestamp INTEGER,"
                        "deletion_timestamp INTEGER"
                        ");")) {
            throw std::runtime_error(
                std::format("Failed to ensure notes table: ",
                            query.lastError().text().toStdString()));
        }
    }

    void Note::bindQueryChild(QSqlQuery& query) const {
        query.bindValue(":content", QString::fromStdString(content_));
    }

}  // namespace abregefeur::data
