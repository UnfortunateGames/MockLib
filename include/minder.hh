#pragma once
#include <chrono>
#include <string>

static constexpr int HOUR_IN_SEC = 3600;
static constexpr int MINUTE_IN_SEC = 60;
static constexpr int ALARM_SIZE = 128;

struct Minder {
    using sec = std::chrono::seconds;
    sec elapsed{0};
    sec alarms[ALARM_SIZE];
    int size;
    bool advance(sec advance_by = sec{1}) {
        elapsed += advance_by;
        for (int i{size - 1}; i >= 0; i--) {
            if (elapsed == alarms[i]) {
                return true;
            }
        }
        return false;
    }
    void set_alarm(sec in) {
        alarms[size++] = in;
    }
    void alarms_pop_front() {
        size--;
    }
};

// Formatted
struct Clock : Minder {
    using mnt = std::chrono::minutes;
    using hour = std::chrono::hours;
    std::string nowF() {
        std::string out{};
        out += std::to_string(
            elapsed.count() / HOUR_IN_SEC
        ) + ":"
            + std::to_string(
            (elapsed.count() % HOUR_IN_SEC) / MINUTE_IN_SEC
        ) + ":"
            + std::to_string(
            elapsed.count() % MINUTE_IN_SEC
        );
        return out;
    }
};
