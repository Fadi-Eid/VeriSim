#include "Vverisim.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>
#include <chrono>

vluint64_t sim_time = 0;            // simulation time (picoseconds)
int clock_period_ps = 10'000;    // Clock Frequency = 100 MHz


int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vverisim* top = new Vverisim;
    VerilatedVcdC* tfp = new VerilatedVcdC;

    Verilated::traceEverOn(true);        // enable tracing
    top->trace(tfp, 99);                 // 99 = levels of hierarchy
    tfp->open("dump.vcd");

    // Initialization
    top->clk = 0;
    top->led = 0;

    for(int i=0; i<1000; i++) {   
        top->clk = !top->clk;
        top->eval();
        sim_time += clock_period_ps / 2;
        tfp->dump(sim_time);   
    }
    
    // Cleanup
    tfp->close();
    delete top;
    return 0;
}
