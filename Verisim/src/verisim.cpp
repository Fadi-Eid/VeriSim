#include "Vverisim.h"
#include "verilated.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <pthread.h>
#include <sched.h>

// Global simulation time in picoseconds
vluint64_t sim_time = 0;

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vverisim* top = new Vverisim;

    // --- CPU pinning (pin to core 0) ---
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) != 0) {
        std::cerr << "Warning: Failed to pin thread to CPU core\n";
    }

    // ---- PARAMETERS ----
    const double clk_freq_hz = 5e6;             // desired clock frequency
    const int execution_duration_s = 200;        // total simulated seconds

    const vluint64_t clock_period_ps = static_cast<vluint64_t>(1e12 / clk_freq_hz); // ps
    const int half_cycles_per_sec = static_cast<int>(clk_freq_hz * 2);              // 2 edges per cycle

    // Initialization
    top->clk = 0;
    top->led = 0;
    top->eval();

    auto start = std::chrono::high_resolution_clock::now(); // Current time
    int led_state = 0;

    for (int cycle = 0; cycle < execution_duration_s * half_cycles_per_sec; cycle++) {
        // Toggle clock
        top->clk = !top->clk;
        top->eval();

        if ((int)top->led != led_state) {
            std::cout << "LED Toggled" << std::endl;
            led_state = (int)top->led;
        }

        // Update simulation time
        sim_time += clock_period_ps / 2;

        // Compute target wall-clock time
        auto target = start + std::chrono::nanoseconds(sim_time / 1000);

        // Busy wait
        while (std::chrono::high_resolution_clock::now() < target) {
            // spin
        }

        // Print once per simulated second
        if (cycle % half_cycles_per_sec == 0 && cycle > 0) {
            auto now = std::chrono::high_resolution_clock::now();
            auto wall_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
            std::cout << std::fixed << std::setprecision(3)
                      << "Simulated time = " << (sim_time / 1e6) << " us"
                      << ", Wall time = " << wall_elapsed << " ms" << std::endl;
        }
    }

    // Cleanup
    delete top;
    return 0;
}
