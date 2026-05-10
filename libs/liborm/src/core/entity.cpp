#include <qsqldatabase.h>
#include <liborm/entity.hpp>

#include <QDateTime>
#include <QSqlQuery>
#include <QUuid>
#include <optional>

#include <liborm/utils/timestamp.hpp>
#include <stdexcept>

namespace liborm {

    Entity::Entity()
        : id_(QUuid::createUuid()),
          creationTimestamp_(QDateTime::currentDateTimeUtc()),
          updateTimestamp_(std::nullopt),
          deletionTimestamp_(std::nullopt) {}

    Entity::Entity(const QUuid& id, const QDateTime& creationTimestamp,
                   const std::optional<QDateTime>& updateTimestamp,
                   const std::optional<QDateTime>& deletionTimestamp)
        : id_(std::move(id)),
          creationTimestamp_(std::move(creationTimestamp)),
          updateTimestamp_(std::move(updateTimestamp)),
          deletionTimestamp_(std::move(deletionTimestamp)) {};

    Entity::Entity(const QSqlQuery& queryResult)
        : id_(queryResult.value(0).toString()),
          creationTimestamp_(
              utils::fromTimestampMs(queryResult.value(1).toLongLong())),
          updateTimestamp_(queryResult.value(2).isNull()
                               ? std::nullopt
                               : std::make_optional(utils::fromTimestampMs(
                                     queryResult.value(2).toLongLong()))),
          deletionTimestamp_(queryResult.value(3).isNull()
                                 ? std::nullopt
                                 : std::make_optional(utils::fromTimestampMs(
                                       queryResult.value(3).toLongLong()))) {}

    const std::string& Entity::getTableName() {
        throwNotImplementedStaticMethod();
    }

    const std::string& Entity::getCols() {
        throwNotImplementedStaticMethod();
    }

    const std::string& Entity::getInsertQuery() {
        throwNotImplementedStaticMethod();
    }

    const std::string& Entity::getUpdateQuery() {
        throwNotImplementedStaticMethod();
    }

    void Entity::setupTable(const QSqlDatabase& database) {
        throwNotImplementedStaticMethod();
    }

    const QUuid& Entity::getId() const {
        return id_;
    }

    const QDateTime& Entity::getCreationTimestamp() const {
        return creationTimestamp_;
    }

    const std::optional<QDateTime>& Entity::getUpdateTimestamp() const {
        return updateTimestamp_;
    }

    const std::optional<QDateTime>& Entity::getDeletionTimestamp() const {
        return deletionTimestamp_;
    }

    void Entity::setUpdateTimestamp() {
        setUpdateTimestamp(QDateTime::currentDateTimeUtc());
    }

    void Entity::setUpdateTimestamp(const QDateTime& updateTimestamp) {
        updateTimestamp_ = std::move(updateTimestamp);
    }

    void Entity::setDeletionTimestamp() {
        setDeletionTimestamp(QDateTime::currentDateTimeUtc());
    }

    void Entity::setDeletionTimestamp(const QDateTime& deletionTimestamp) {
        deletionTimestamp_ = std::move(deletionTimestamp);
    }

    void Entity::bindQuery(QSqlQuery& query) const {
        bindQueryBase(query);
        bindQueryChild(query);
    }

    void Entity::bindQueryBase(QSqlQuery& query) const {
        query.bindValue(":id", id_.toString(QUuid::WithoutBraces));

        query.bindValue(":creation_timestamp",
                        utils::toTimestampMs(creationTimestamp_));

        query.bindValue(
            ":update_timestamp",
            updateTimestamp_
                ? QVariant::fromValue(utils::toTimestampMs(*updateTimestamp_))
                : QVariant());

        query.bindValue(
            ":deletion_timestamp",
            deletionTimestamp_
                ? QVariant::fromValue(utils::toTimestampMs(*deletionTimestamp_))
                : QVariant());
    }

    [[noreturn]] void Entity::throwNotImplementedStaticMethod() {
        throw new std::runtime_error(
            "Static method not implemented for class. Please implement it.");
    }

}  // namespace liborm
