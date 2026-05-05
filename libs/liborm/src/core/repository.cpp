#include <liborm/repository.hpp>

namespace liborm::repository {

    void save(Entity& entity) {
        const QSqlDatabase database = requireDatabase();

        const QString templatedExistsQuery(
            std::format("SELECT 1 FROM {} WHERE id = :id LIMIT 1;",
                        entity.getTableName())
                .c_str());

        const QUuid& id = entity.getId();
        const QString& id_str = id.toString(QUuid::WithoutBraces);

        QSqlQuery existsQuery(database);
        existsQuery.prepare(templatedExistsQuery);
        existsQuery.bindValue(":id", id_str);

        if (!existsQuery.exec()) {
            throw std::runtime_error(std::format(
                "Failed to verify {} existence: {}", id_str.toStdString(),
                existsQuery.lastError().text().toStdString()));
        }

        const bool exists = existsQuery.next();

        if (exists) {
            entity.setUpdateTimestamp();

            QSqlQuery updateQuery(database);
            updateQuery.prepare(entity.getUpdateQuery().c_str());
            entity.bindQuery(updateQuery);

            if (!updateQuery.exec()) {
                throw std::runtime_error(std::format(
                    "Failed to update note {}: {}", id_str.toStdString(),
                    updateQuery.lastError().text().toStdString()));
            }

            return;
        }

        QSqlQuery insertQuery(database);
        insertQuery.prepare(entity.getInsertQuery().c_str());
        entity.bindQuery(insertQuery);

        if (!insertQuery.exec()) {
            throw std::runtime_error(
                std::format("Failed to insert note: {}",
                            insertQuery.lastError().text().toStdString()));
        }
    }

    void remove(Entity& entity) {
        entity.setDeletionTimestamp();
        save(entity);
    }

}  // namespace liborm::repository
