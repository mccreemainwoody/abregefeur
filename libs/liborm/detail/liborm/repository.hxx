#pragma once

#include <liborm/repository.hpp>

#include <QSqlError>
#include <QUuid>

#include <liborm/database.hpp>
#include <liborm/utils/timestamp.hpp>

namespace liborm::repository {

    namespace {

        QSqlDatabase requireDatabase() {
            return Database::getInstance()->getDatabase();
        }

    }  // namespace

    template <TEntity T>
    std::vector<T> find() {
        const QSqlDatabase database = requireDatabase();
        QSqlQuery query(database);

        query.setForwardOnly(true);

        const QString templatedQuery(
            std::format("SELECT id, creation_timestamp, update_timestamp, "
                        "deletion_timestamp, {} "
                        "FROM {} WHERE id = :id;",
                        T::getCols(), T::getTableName())
                .c_str());

        if (!query.exec()) {
            throw std::runtime_error(
                std::format("Failed to query notes: ",
                            query.lastError().text().toStdString()));
        }

        const int results_size = query.size();
        std::vector<T> results;

        if (results_size >= 0) {
            results.reserve(results_size);
        }

        while (query.next()) {
            results.push_back(T(query));
        }

        return results;
    }

    template <TEntity T>
    std::optional<T> find(const QUuid& id) {
        QSqlDatabase database = requireDatabase();
        QSqlQuery query(database);

        const QString templatedQuery(
            std::format("SELECT id, creation_timestamp, update_timestamp, "
                        "deletion_timestamp, {} "
                        "FROM {} WHERE id = :id;",
                        T::getCols(), T::getTableName())
                .c_str());

        query.prepare(templatedQuery);
        query.bindValue(":id", id.toString(QUuid::WithoutBraces));

        if (!query.exec()) {
            throw std::runtime_error(std::format(
                "Failed to query {}: {}", id.toString().toStdString(),
                query.lastError().text().toStdString()));
        }

        if (!query.next()) {
            return std::nullopt;
        }

        return T(query);
    }

}  // namespace liborm::repository
