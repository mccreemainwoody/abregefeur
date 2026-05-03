#include <abregefeur/data/note.hpp>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <format>

#include <abregefeur/data/database.hpp>
#include <abregefeur/utils/timestamp.hpp>

namespace abregefeur::data {

    namespace {

        QSqlDatabase requireDatabase() {
            return Database::getInstance()->getDatabase();
        }

    }  // namespace

    Note::Note(const std::string& content)
        : m_id(QUuid::createUuid()),
          m_content(content),
          m_creationTimestamp(QDateTime::currentDateTimeUtc()),
          m_updateTimestamp(std::nullopt),
          m_deletionTimestamp(std::nullopt) {}

    Note::Note(const QUuid& id, const std::string& content,
               const QDateTime& creationTimestamp,
               const std::optional<QDateTime>& updateTimestamp,
               const std::optional<QDateTime>& deletionTimestamp)
        : m_id(std::move(id)),
          m_content(std::move(content)),
          m_creationTimestamp(std::move(creationTimestamp)),
          m_updateTimestamp(std::move(updateTimestamp)),
          m_deletionTimestamp(std::move(deletionTimestamp)) {}

    Note Note::fromDatabase(const QSqlQuery& queryResult) {
        const QUuid id(queryResult.value(0).toString());

        const std::string content =
            queryResult.value(1).toString().toStdString();

        const QDateTime creationTimestamp =
            utils::fromTimestampMs(queryResult.value(2).toLongLong());

        const auto updateTimestampValue = queryResult.value(3);
        const std::optional<QDateTime> updateTimestamp =
            updateTimestampValue.isNull()
                ? std::nullopt
                : std::make_optional(utils::fromTimestampMs(
                      updateTimestampValue.toLongLong()));

        const auto deletionTimestampValue = queryResult.value(4);
        const std::optional<QDateTime> deletionTimestamp =
            deletionTimestampValue.isNull()
                ? std::nullopt
                : std::make_optional(utils::fromTimestampMs(
                      deletionTimestampValue.toLongLong()));

        return Note(std::move(id), std::move(content),
                    std::move(creationTimestamp), std::move(updateTimestamp),
                    std::move(deletionTimestamp));
    }

    void Note::setupTable(const QSqlDatabase& database) {
        QSqlQuery query(database);

        if (!query.exec("CREATE TABLE IF NOT EXISTS notes ("
                        "id TEXT PRIMARY KEY,"
                        "content TEXT NOT NULL,"
                        "creation_timestamp INTEGER NOT NULL,"
                        "update_timestamp INTEGER,"
                        "deletion_timestamp INTEGER"
                        ");")) {
            throw std::runtime_error(
                std::format("Failed to ensure notes table: ",
                            query.lastError().text().toStdString()));
        }
    }

    void Note::setupQuery(QSqlQuery& query) {
        query.bindValue(":id", m_id.toString(QUuid::WithoutBraces));

        query.bindValue(":content", QString::fromStdString(m_content));

        query.bindValue(":creation_timestamp",
                        utils::toTimestampMs(m_creationTimestamp));

        query.bindValue(
            ":update_timestamp",
            m_updateTimestamp
                ? QVariant::fromValue(utils::toTimestampMs(*m_updateTimestamp))
                : QVariant());

        query.bindValue(":deletion_timestamp",
                        m_deletionTimestamp
                            ? QVariant::fromValue(
                                  utils::toTimestampMs(*m_deletionTimestamp))
                            : QVariant());
    }

    std::vector<Note> Note::find() {
        QSqlDatabase database = requireDatabase();
        QSqlQuery query(database);

        query.setForwardOnly(true);
        query.prepare(
            "SELECT id, content, creation_timestamp, update_timestamp, "
            "deletion_timestamp "
            "FROM notes;");

        if (!query.exec()) {
            throw std::runtime_error(
                std::format("Failed to query notes: ",
                            query.lastError().text().toStdString()));
        }

        const int results_size = query.size();
        std::vector<Note> results;

        if (results_size >= 0) {
            qDebug() << results_size;
            results.reserve(results_size);
        }

        while (query.next()) {
            results.push_back(fromDatabase(query));
        }

        return results;
    }

    std::optional<Note> Note::find(const QUuid& id) {
        QSqlDatabase database = requireDatabase();
        QSqlQuery query(database);

        query.prepare(
            "SELECT id, content, creation_timestamp, update_timestamp, "
            "deletion_timestamp "
            "FROM notes WHERE id = :id;");
        query.bindValue(":id", id.toString(QUuid::WithoutBraces));

        if (!query.exec()) {
            throw std::runtime_error(std::format(
                "Failed to query note {}: {}", id.toString().toStdString(),
                query.lastError().text().toStdString()));
        }

        if (!query.next()) {
            return std::nullopt;
        }

        return fromDatabase(query);
    }

    const QUuid& Note::getId() const {
        return m_id;
    }

    const std::string& Note::getContent() const {
        return m_content;
    }

    const QDateTime& Note::getCreationTimestamp() const {
        return m_creationTimestamp;
    }

    const std::optional<QDateTime>& Note::getUpdateTimestamp() const {
        return m_updateTimestamp;
    }

    const std::optional<QDateTime>& Note::getDeletionTimestamp() const {
        return m_deletionTimestamp;
    }

    void Note::setContent(const std::string& content) {
        m_content = content;
    }

    void Note::save() {
        QSqlDatabase database = requireDatabase();

        QSqlQuery existsQuery(database);
        existsQuery.prepare("SELECT 1 FROM notes WHERE id = :id LIMIT 1;");
        existsQuery.bindValue(":id", m_id.toString(QUuid::WithoutBraces));

        if (!existsQuery.exec()) {
            throw std::runtime_error(
                std::format("Failed to verify note {} existence: {}",
                            m_id.toString().toStdString(),
                            existsQuery.lastError().text().toStdString()));
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

            setupQuery(updateQuery);

            if (!updateQuery.exec()) {
                throw std::runtime_error(
                    std::format("Failed to update note {}: {}",
                                m_id.toString().toStdString(),
                                updateQuery.lastError().text().toStdString()));
            }

            return;
        }

        QSqlQuery insertQuery(database);

        insertQuery.prepare(
            "INSERT INTO notes (id, content, creation_timestamp, "
            "update_timestamp, deletion_timestamp) "
            "VALUES (:id, :content, :creation_timestamp, :update_timestamp, "
            ":deletion_timestamp);");

        setupQuery(insertQuery);

        if (!insertQuery.exec()) {
            throw std::runtime_error(
                std::format("Failed to insert note: {}",
                            insertQuery.lastError().text().toStdString()));
        }
    }

    void Note::remove() {
        m_deletionTimestamp = QDateTime::currentDateTimeUtc();
        save();
    }

}  // namespace abregefeur::data
