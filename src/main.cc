#include <chrono>
#include <iostream>
#include <thread>

#include <minder.hh>
#include <scopeguard.hh>
#include <smallvec.hh>
#include <timer.hh>

using steady = std::chrono::steady_clock;
using sec = std::chrono::seconds;
using ms = std::chrono::milliseconds;

void secret_message() {
    std::cout << "I <3 u!";
}

void intended_minder_tests() {
    // // MINDER TESTS
    // Alarms = Goals
    Minder kitchen_minder{};
    // Goals
    kitchen_minder.set_alarm(sec{2});
    kitchen_minder.set_alarm(sec{4});
    kitchen_minder.set_alarm(sec{5});
    kitchen_minder.set_alarm(sec{9});
    // Loop!
    for (int i{0u}; i < 10; i++) {
        if (
            bool x =
                kitchen_minder.advance();
            x
        ) std::cout << "DING!" << std::endl;
        else std::cout << "..." << std::endl;
    }
    /* Expected Output:
     * ...
     * DING!
     * ...
     * DING!
     * DING!
     * ...
     * ...
     * ...
     * DING!
     * ...
     */
}

void intended_smallvec_tests() {
    // // Small Vector
    // Aww vector's so cute!
    SmallVec vector;
    vector.push_back(19u);
    vector.push_back(42u);
    vector.push_back(255u);
    vector.pop_back(); // remove that almost overflowing integer!
    // Read back
    std::cout
        << "[0] -> " << (int) vector[0] << std::endl
        << "[1] -> " << (int) vector[1] << std::endl;
    
    // LETS CRASH OUT!
    vector.debug_assert();
    /* Expected Output:
     * [0] -> 19
     * [1] -> 42
     * NO ABORT
     */
}

void intended_stopwatch_tests() {
    // Time shenanigans
    Stopwatch watch; // Raw!
    watch.start();
    std::this_thread::sleep_for(ms{1500}); // Sleep tight little metal
    watch.stop();
    StopwatchFMT formatted{watch}; // Let's read it
    std::cout
        << formatted.now_fmt() << std::endl
        << formatted.status_fmt() << std::endl;
    watch.reset(steady::now()); // Reset for another run
    watch.start(); // Start up to see RUNNING
    std::cout << formatted.status_fmt() << std::endl;
    std::this_thread::sleep_for(ms{500});
    watch.stop(); // STOP
    std::this_thread::sleep_for(ms{1000}); // This should not add up
    std::cout << formatted.now_fmt() << std::endl;
    watch.start();
    std::this_thread::sleep_for(ms{500});
    std::cout << formatted.now_fmt() << std::endl;
    /* Expected Output:
     * 1-2s
     * Clock is STOPPED.
     * Clock is RUNNING.
     * 0-1s
     * 1s
     */
}

void unintended_stopwatch_tests() {
    Stopwatch watch;

    std::cout << "Stop test: ";
    if (!watch.status()) std::cout << "STOPPED ";
    else std::cout << "running? you're not supposed to see this. ";
    
    watch.stop(); // if not running returns before anything executes.
    
    if (!watch.status()) std::cout << "STOPPED" << std::endl;
    else std::cout << "running? you're not supposed to see this." << std::endl;
    
    watch.start();
    
    std::cout << "Start test: ";
    if (watch.status()) std::cout << "RUNNING ";
    else std::cout << "stopped? what is happening bro. ";
    
    watch.start(); // same case as stop.
    
    if (watch.status()) std::cout << "RUNNING" << std::endl;
    else std::cout << "stopped? what is happening bro. " << std::endl;
    /* Expected Output:
     * Stop test: STOPPED STOPPED
     * Start test: RUNNING RUNNING
     * I <3 u! // <- scopeguard secret message
     */
}

int main() {
    intended_minder_tests();
    // sEcReT mEsSaGe!
    ScopeGuard secret{secret_message};
    intended_smallvec_tests();
    intended_stopwatch_tests();
    unintended_stopwatch_tests();
    // Others crash or won't compile if used incorrectly
    // So no unintended tests for them sadly.
    return 0;
}
