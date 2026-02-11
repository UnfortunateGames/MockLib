#pragma once
#include <chrono>
#include <string>

using steady = std::chrono::steady_clock;
using duration = steady::duration;

static constexpr int HOUR_IN_SECONDS = 3600;
static constexpr int MINUTE_IN_SECONDS = 60;

struct Stopwatch {
    using time_p = steady::time_point;
    void start() {
        if (running) return;
        start_point = steady::now();
        running = true;
    }
    void reset(time_p new_time) {
        start_point = new_time;
        total_elapsed = duration{0};
        running = false;
    }
    duration elapsed() {
        if (!running) return total_elapsed;
        return total_elapsed + (steady::now() - start_point);
    }
    bool status() {
        return running;
    }
    void stop() {
        if (!running) return;
        total_elapsed += steady::now() - start_point;
        running = false;
    }
    private:
        duration total_elapsed{0};
        time_p start_point;
        bool running = false;
};

struct StopwatchFMT {
    Stopwatch& watch;
    std::string now_fmt() {
        std::string out{};
        int64_t elapsed = std::chrono::duration_cast
            <std::chrono::seconds>
            (watch.elapsed())
            .count();
        int hours = elapsed / HOUR_IN_SECONDS;
        int minutes = (elapsed % HOUR_IN_SECONDS) / MINUTE_IN_SECONDS;
        int seconds = elapsed % MINUTE_IN_SECONDS;
        if (hours != 0)
            out += std::to_string(hours) + "h ";
        if (minutes != 0)
            out += std::to_string(minutes) + "m ";
        out += std::to_string(seconds) + "s";
        return out;
    }
    std::string status_fmt() {
        if (watch.status()) return "Clock is RUNNING.";
        return "Clock is STOPPED.";
    }
};
