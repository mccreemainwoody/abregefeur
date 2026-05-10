#pragma once

#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QUuid>
#include <filesystem>
#include <liborm/entity.hpp>
#include <optional>
#include <string>

#include <abregefeur/data/artifact_type.hpp>

namespace abregefeur::data {

    class Artifact : public liborm::Entity {
       public:
        static const std::string& getTableName();
        static const std::string& getCols();
        static const std::string& getInsertQuery();
        static const std::string& getUpdateQuery();
        static void setupTable(const QSqlDatabase& database);

        Artifact(const ArtifactType type, const std::filesystem::path& path);
        Artifact(const QSqlQuery& queryResult);

        const ArtifactType getType() const;
        const std::filesystem::path& getPath() const;

       private:
        static const std::string tableName_;
        static const std::string cols_;
        static const std::string insertQuery_;
        static const std::string updateQuery_;

        Artifact(const QUuid& id, const ArtifactType type,
                 const std::filesystem::path& path,
                 const QDateTime& creationTimestamp,
                 const std::optional<QDateTime>& updateTimestamp,
                 const std::optional<QDateTime>& deletionTimestamp);

        void bindQueryChild(QSqlQuery& query) const;

        const ArtifactType type_;
        const std::filesystem::path path_;
    };

}  // namespace abregefeur::data
