#pragma once

#include <QDateTime>
#include <QSqlQuery>
#include <QUuid>
#include <optional>
#include <string>

namespace liborm {

    class Entity {
       public:
        static const std::string& getTableName();
        static const std::string& getCols();
        static const std::string& getInsertQuery();
        static const std::string& getUpdateQuery();

        const QUuid& getId() const;
        const QDateTime& getCreationTimestamp() const;
        const std::optional<QDateTime>& getUpdateTimestamp() const;
        const std::optional<QDateTime>& getDeletionTimestamp() const;

        void setUpdateTimestamp();
        void setUpdateTimestamp(const QDateTime& updateTimestamp);
        void setDeletionTimestamp();
        void setDeletionTimestamp(const QDateTime& deletionTimestamp);

        void bindQuery(QSqlQuery& query) const;

       protected:
        Entity();
        Entity(const QUuid& id, const QDateTime& creationTimestamp,
               const std::optional<QDateTime>& updateTimestamp,
               const std::optional<QDateTime>& deletionTimestamp);
        Entity(const QSqlQuery& queryResult);

        void bindQueryBase(QSqlQuery& query) const;
        virtual void bindQueryChild(QSqlQuery& query) const = 0;

        const QUuid id_;
        const QDateTime creationTimestamp_;
        std::optional<QDateTime> updateTimestamp_;
        std::optional<QDateTime> deletionTimestamp_;

       private:
        [[noreturn]] static void throwNotImplementedStaticMethod();
    };

}  // namespace liborm
