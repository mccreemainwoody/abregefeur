#pragma once

#include <QDateTime>
#include <QTimeZone>
#include <QtTypes>

namespace liborm::utils {

    inline qint64 toTimestampMs(const QDateTime& dateTime);

    inline QDateTime fromTimestampMs(const qint64 timestampMs);

}  // namespace liborm::utils

#include <liborm/utils/timestamp.hxx>
