#include <liborm/database.hpp>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <format>
#include <memory>

namespace liborm {

    Database::Database(const QSqlDatabase& database)
        : database_(std::move(database)) {};

    std::shared_ptr<Database> Database::getInstance() {
        if (!instance_) {
            initializeConnection();
        }

        return instance_;
    }

    const QSqlDatabase& Database::getDatabase() const {
        return database_;
    }

    void Database::initializeConnection() {
        QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");

        database.setDatabaseName("abregefeur.db");

        if (!database.isValid()) {
            throw std::runtime_error("Database is invalid.");
        }

        if (!database.isOpen() && !database.open()) {
            throw std::runtime_error(
                std::format("Failed to open sqlite database: {}",
                            database.lastError().text().toStdString()));
        }

        Database::instance_ = std::shared_ptr<Database>(new Database(database));
    }

    std::shared_ptr<Database> Database::instance_ = nullptr;

}  // namespace liborm
