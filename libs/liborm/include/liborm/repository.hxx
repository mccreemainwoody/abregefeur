#pragma once

#include <liborm/repository.hpp>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QUuid>
#include <format>
#include <stdexcept>

#include <liborm/database.hpp>
#include <liborm/utils/timestamp.hpp>
#include <utility>

namespace liborm::repository {

    namespace {

        QSqlDatabase requireDatabase() {
            return Database::getInstance()->getDatabase();
        }

    }  // namespace

    template <TEntity T>
    std::vector<T> find() {
        const QSqlDatabase database = requireDatabase();
        T::setupTable(database);

        const QString templatedQuery(
            std::format("SELECT id, creation_timestamp, update_timestamp, "
                        "deletion_timestamp, {} "
                        "FROM {};",
                        T::getCols(), T::getTableName())
                .c_str());

        QSqlQuery query(database);
        query.setForwardOnly(true);

        if (!query.exec(templatedQuery)) {
            throw std::runtime_error(
                std::format("Failed to query {}: {}", T::getTableName(),
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

        return std::move(results);
    }

    template <TEntity T>
    std::optional<T> find(const QUuid& id) {
        const QSqlDatabase database = requireDatabase();
        T::setupTable(database);

        const QString templatedQuery(
            std::format("SELECT id, creation_timestamp, update_timestamp, "
                        "deletion_timestamp, {} "
                        "FROM {} WHERE id = :id;",
                        T::getCols(), T::getTableName())
                .c_str());

        QSqlQuery query(database);
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

    template <TEntity T>
    void save(T& entity) {
        const QSqlDatabase database = requireDatabase();

        const QString templatedExistsQuery(
            std::format("SELECT 1 FROM {} WHERE id = :id LIMIT 1;",
                        T::getTableName())
                .c_str());

        const QUuid& id = entity.getId();
        const QString& id_str = id.toString(QUuid::WithoutBraces);

        QSqlQuery existsQuery(database);
        existsQuery.prepare(templatedExistsQuery);
        existsQuery.bindValue(":id", id_str);

        if (!existsQuery.exec()) {
            throw new std::runtime_error(
                std::format("Failed to verify {} existence in {}: {}",
                            id_str.toStdString(), T::getTableName(),
                            existsQuery.lastError().text().toStdString()));
        }

        const bool exists = existsQuery.next();

        if (exists) {
            entity.setUpdateTimestamp();

            QSqlQuery updateQuery(database);
            updateQuery.prepare(entity.getUpdateQuery().c_str());
            entity.bindQuery(updateQuery);

            if (!updateQuery.exec()) {
                throw new std::runtime_error(
                    std::format("Failed to update {} {}: {}",
                                entity.getTableName(), id_str.toStdString(),
                                updateQuery.lastError().text().toStdString()));
            }

            return;
        }

        QSqlQuery insertQuery(database);
        insertQuery.prepare(entity.getInsertQuery().c_str());
        entity.bindQuery(insertQuery);

        if (!insertQuery.exec()) {
            throw new std::runtime_error(std::format(
                "Failed to insert into {}: {}", entity.getTableName(),
                insertQuery.lastError().text().toStdString()));
        }
    }

    template <TEntity T>
    void remove(T& entity) {
        entity.setDeletionTimestamp();
        save(entity);
    }

}  // namespace liborm::repository
