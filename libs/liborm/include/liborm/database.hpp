#pragma once

#include <QSqlDatabase>
#include <memory>

namespace liborm {

    class Database {
       public:
        Database(Database&) = delete;
        void operator=(Database&) = delete;
        Database& operator=(Database&&) = delete;

        static std::shared_ptr<Database> getInstance();

        const QSqlDatabase& getDatabase() const;

       private:
        Database(const QSqlDatabase& database);

        static void initializeConnection();
        static std::shared_ptr<Database> instance_;

        const QSqlDatabase database_;
    };

}  // namespace liborm
