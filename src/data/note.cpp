#include "note.hpp"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTimeZone>

#include <stdexcept>
#include <utility>

#include <timestamp.hpp>

namespace abregefeur::data {

    namespace {

        QSqlDatabase requireDatabase() {
            QSqlDatabase database = QSqlDatabase::database();

            if (!database.isValid()) {
                throw std::runtime_error(
                    "No default database connection is configured.");
            }

            if (!database.isOpen() && !database.open()) {
                throw std::runtime_error(("Failed to open sqlite database: " +
                                          database.lastError().text())
                                             .toStdString());
            }
            return database;
        }

        void ensureNotesTableExists(QSqlDatabase& database) {
            QSqlQuery query(database);
            if (!query.exec("CREATE TABLE IF NOT EXISTS notes ("
                            "id TEXT PRIMARY KEY,"
                            "content TEXT NOT NULL,"
                            "creation_timestamp INTEGER NOT NULL,"
                            "update_timestamp INTEGER NOT NULL,"
                            "deletion_timestamp INTEGER NOT NULL"
                            ");")) {
                throw std::runtime_error(("Failed to ensure notes table: " +
                                          query.lastError().text())
                                             .toStdString());
            }
        }
    }  // namespace

    Note::Note(std::string content)
        : m_id(QUuid::createUuid()),
          m_content(std::move(content)),
          m_creationTimestamp(QDateTime::currentDateTimeUtc()),
          m_updateTimestamp(utils::zeroTimestamp()),
          m_deletionTimestamp(utils::zeroTimestamp()) {}

    Note Note::fromDatabase(QUuid id, std::string content,
                            QDateTime creationTimestamp,
                            QDateTime updateTimestamp,
                            QDateTime deletionTimestamp) {
        return Note(std::move(id), std::move(content),
                    std::move(creationTimestamp), std::move(updateTimestamp),
                    std::move(deletionTimestamp));
    }

    Note Note::find(const QUuid& id) {
        QSqlDatabase database = requireDatabase();
        ensureNotesTableExists(database);

        QSqlQuery query(database);
        query.prepare(
            "SELECT id, content, creation_timestamp, update_timestamp, "
            "deletion_timestamp "
            "FROM notes WHERE id = :id;");
        query.bindValue(":id", id.toString(QUuid::WithoutBraces));

        if (!query.exec()) {
            throw std::runtime_error(
                ("Failed to query note: " + query.lastError().text())
                    .toStdString());
        }
        if (!query.next()) {
            throw std::runtime_error("Note not found.");
        }

        const QUuid noteId(query.value(0).toString());
        const std::string content = query.value(1).toString().toStdString();
        const QDateTime creationTimestamp =
            utils::fromTimestampMs(query.value(2).toLongLong());
        const QDateTime updateTimestamp =
            utils::fromTimestampMs(query.value(3).toLongLong());
        const QDateTime deletionTimestamp =
            utils::fromTimestampMs(query.value(4).toLongLong());

        return fromDatabase(noteId, content, creationTimestamp, updateTimestamp,
                            deletionTimestamp);
    }

    QUuid Note::getId() const {
        return m_id;
    }

    std::string Note::getContent() const {
        return m_content;
    }

    QDateTime Note::getCreationTimestamp() const {
        return m_creationTimestamp;
    }

    QDateTime Note::getUpdateTimestamp() const {
        return m_updateTimestamp;
    }

    QDateTime Note::getDeletionTimestamp() const {
        return m_deletionTimestamp;
    }

    void Note::setContent(std::string content) {
        m_content = std::move(content);
    }

    void Note::save() {
        QSqlDatabase database = requireDatabase();
        ensureNotesTableExists(database);

        QSqlQuery existsQuery(database);
        existsQuery.prepare("SELECT 1 FROM notes WHERE id = :id LIMIT 1;");
        existsQuery.bindValue(":id", m_id.toString(QUuid::WithoutBraces));

        if (!existsQuery.exec()) {
            throw std::runtime_error(("Failed to verify note existence: " +
                                      existsQuery.lastError().text())
                                         .toStdString());
        }
        const bool exists = existsQuery.next();

        if (exists) {
            m_updateTimestamp = QDateTime::currentDateTimeUtc();

            QSqlQuery updateQuery(database);
            updateQuery.prepare(
                "UPDATE notes "
                "SET content = :content, update_timestamp = :update_timestamp, "
                "deletion_timestamp = :deletion_timestamp "
                "WHERE id = :id;");
            updateQuery.bindValue(":content",
                                  QString::fromStdString(m_content));
            updateQuery.bindValue(":update_timestamp",
                                  utils::toTimestampMs(m_updateTimestamp));
            updateQuery.bindValue(":deletion_timestamp",
                                  utils::toTimestampMs(m_deletionTimestamp));
            updateQuery.bindValue(":id", m_id.toString(QUuid::WithoutBraces));

            if (!updateQuery.exec()) {
                throw std::runtime_error(
                    ("Failed to update note: " + updateQuery.lastError().text())
                        .toStdString());
            }
            return;
        }

        QSqlQuery insertQuery(database);
        insertQuery.prepare(
            "INSERT INTO notes (id, content, creation_timestamp, "
            "update_timestamp, deletion_timestamp) "
            "VALUES (:id, :content, :creation_timestamp, :update_timestamp, "
            ":deletion_timestamp);");
        insertQuery.bindValue(":id", m_id.toString(QUuid::WithoutBraces));
        insertQuery.bindValue(":content", QString::fromStdString(m_content));
        insertQuery.bindValue(":creation_timestamp",
                              utils::toTimestampMs(m_creationTimestamp));
        insertQuery.bindValue(":update_timestamp",
                              utils::toTimestampMs(m_updateTimestamp));
        insertQuery.bindValue(":deletion_timestamp",
                              utils::toTimestampMs(m_deletionTimestamp));

        if (!insertQuery.exec()) {
            throw std::runtime_error(
                ("Failed to insert note: " + insertQuery.lastError().text())
                    .toStdString());
        }
    }

    void Note::remove() {
        m_deletionTimestamp = QDateTime::currentDateTimeUtc();
        save();
    }

    Note::Note(QUuid id, std::string content, QDateTime creationTimestamp,
               QDateTime updateTimestamp, QDateTime deletionTimestamp)
        : m_id(std::move(id)),
          m_content(std::move(content)),
          m_creationTimestamp(std::move(creationTimestamp)),
          m_updateTimestamp(std::move(updateTimestamp)),
          m_deletionTimestamp(std::move(deletionTimestamp)) {}

}  // namespace abregefeur::data
