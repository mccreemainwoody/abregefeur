#include "timestamp.hpp"

namespace abregefeur::utils {

    inline QDateTime zeroTimestamp() {
        return QDateTime::fromMSecsSinceEpoch(0, QTimeZone::UTC);
    }

    inline qint64 toTimestampMs(const QDateTime& dateTime) {
        return dateTime.toMSecsSinceEpoch();
    }

    inline QDateTime fromTimestampMs(qint64 timestampMs) {
        return QDateTime::fromMSecsSinceEpoch(timestampMs, QTimeZone::UTC);
    }

}  // namespace abregefeur::utils
