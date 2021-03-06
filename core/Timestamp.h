//
// Created by suncx on 2020/8/8.
//

#ifndef REACTOR_TIMESTAMP_H
#define REACTOR_TIMESTAMP_H

#include <cstdint>
#include <string>
#include <cstring>
#include <cinttypes>
#include <ctime>
#include "Exception.h"

using std::string;

class Timestamp final {
private:
    int64_t microsecond_since_epoch;     // since 1970-01-01 00:00:00 +0000 (UTC).

    static const int microseconds_per_second = 1000 * 1000;

    friend double time_diff(const Timestamp &high, const Timestamp &low);

    friend Timestamp add_time(Timestamp timestamp, double seconds_offset);

public:
    explicit Timestamp(int64_t msSinceEpoch = 0);

    void swap(Timestamp &timestamp);

    string to_string() const;

    string to_fmt_string(bool show_microsecond = false) const;

    static Timestamp now();

    bool operator<(const Timestamp &rhs) const;

    bool operator>(const Timestamp &rhs) const;

    bool operator<=(const Timestamp &rhs) const;

    bool operator>=(const Timestamp &rhs) const;

    bool operator==(const Timestamp &rhs) const;

    bool operator!=(const Timestamp &rhs) const;
};

#endif //REACTOR_TIMESTAMP_H
