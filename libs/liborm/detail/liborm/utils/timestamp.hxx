#include <liborm/utils/timestamp.hpp>

#include <QDateTime>
#include <QTimeZone>

namespace liborm::utils {

    inline qint64 toTimestampMs(const QDateTime& dateTime) {
        return dateTime.toMSecsSinceEpoch();
    }

    inline QDateTime fromTimestampMs(qint64 timestampMs) {
        return QDateTime::fromMSecsSinceEpoch(timestampMs, QTimeZone::UTC);
    }

}  // namespace liborm::utils
