#include <abregefeur/data/artifact.hpp>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <format>
#include <stdexcept>
#include <string>

namespace abregefeur::data {

    const std::string Artifact::tableName_ = "artifacts";
    const std::string Artifact::cols_ = "type, path";
    const std::string Artifact::insertQuery_ =
        "INSERT INTO artifacts (id, type, path, creation_timestamp, "
        "update_timestamp, deletion_timestamp) "
        "VALUES (:id, :type, :path, :creation_timestamp, :update_timestamp, "
        ":deletion_timestamp);";
    const std::string Artifact::updateQuery_ =
        "UPDATE artifacts "
        "SET type = :type, path = :path, update_timestamp = :update_timestamp, "
        "deletion_timestamp = :deletion_timestamp "
        "WHERE id = :id;";

    Artifact::Artifact(const ArtifactType type,
                       const std::filesystem::path& path)
        : liborm::Entity(), type_(type), path_(std::move(path)) {};

    Artifact::Artifact(const QUuid& id, const ArtifactType type,
                       const std::filesystem::path& path,
                       const QDateTime& creationTimestamp,
                       const std::optional<QDateTime>& updateTimestamp,
                       const std::optional<QDateTime>& deletionTimestamp)
        : liborm::Entity(id, creationTimestamp, updateTimestamp,
                         deletionTimestamp),
          type_(type),
          path_(std::move(path)) {};

    Artifact::Artifact(const QSqlQuery& queryResult)
        : liborm::Entity(queryResult),
          type_(static_cast<ArtifactType>(queryResult.value(4).toInt())),
          path_(queryResult.value(5).toString().toStdString()) {};

    const std::string& Artifact::getTableName() {
        return tableName_;
    }

    const std::string& Artifact::getCols() {
        return cols_;
    }

    const std::string& Artifact::getInsertQuery() {
        return insertQuery_;
    }

    const std::string& Artifact::getUpdateQuery() {
        return updateQuery_;
    }

    const ArtifactType Artifact::getType() const {
        return type_;
    }

    const std::filesystem::path& Artifact::getPath() const {
        return path_;
    }

    void Artifact::setupTable(const QSqlDatabase& database) {
        QSqlQuery query(database);

        if (!query.exec("CREATE TABLE IF NOT EXISTS artifacts ("
                        "id TEXT PRIMARY KEY,"
                        "type INTEGER NOT NULL,"
                        "path TEXT NOT NULL,"
                        "creation_timestamp INTEGER NOT NULL,"
                        "update_timestamp INTEGER,"
                        "deletion_timestamp INTEGER"
                        ");")) {
            throw std::runtime_error(
                std::format("Failed to ensure artifacts table: {}",
                            query.lastError().text().toStdString()));
        }
    }

    void Artifact::bindQueryChild(QSqlQuery& query) const {
        query.bindValue(":type", static_cast<int>(type_));
        query.bindValue(":path", QString::fromStdString(path_.string()));
    }

}  // namespace abregefeur::data
