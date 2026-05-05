#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QUuid>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>

#include <liborm/entity.hpp>

namespace liborm::repository {

    template <typename T>
    concept TEntity = std::derived_from<T, Entity> &&
                      requires(T entity, const QSqlDatabase& db,
                               QSqlQuery& query, const QSqlQuery& queryResult) {
                          T(queryResult);
                          { T::setupTable(db) } -> std::same_as<void>;
                          {
                              T::getTableName()
                          } -> std::same_as<const std::string&>;
                          { T::getCols() } -> std::same_as<const std::string&>;
                          { entity.getId() } -> std::same_as<const QUuid&>;
                          { entity.bindQuery(query) } -> std::same_as<void>;
                          { entity.setUpdateTimestamp() } -> std::same_as<void>;
                          {
                              entity.setDeletionTimestamp()
                          } -> std::same_as<void>;
                      };

    template <TEntity T>
    static std::vector<T> find();
    template <TEntity T>
    static std::optional<T> find(const QUuid& id);

    template <TEntity T>
    void save(T& entity);
    void remove(Entity& entity);

}  // namespace liborm::repository

#include <liborm/repository.hxx>
