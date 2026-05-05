#pragma once

#include <QDateTime>

namespace liborm::utils {

    inline qint64 toTimestampMs(const QDateTime& dateTime);

    inline QDateTime fromTimestampMs(qint64 timestampMs);

}  // namespace liborm::utils

#include <liborm/utils/timestamp.hxx>
