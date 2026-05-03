#pragma once

#include <QTimeZone>

namespace abregefeur::utils {

    inline QDateTime zeroTimestamp();

    inline qint64 toTimestampMs(const QDateTime& dateTime);

    inline QDateTime fromTimestampMs(qint64 timestampMs);

}  // namespace abregefeur::utils

#include <abregefeur/utils/timestamp.hxx>
