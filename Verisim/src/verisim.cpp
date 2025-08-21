#include "Vverisim.h"
#include "verilated.h"
#include <iostream>

// Global simulation time in picoseconds
vluint64_t sim_time = 0;

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vverisim* top = new Vverisim;

    
    // Initialization
    top->clk = 0;
    // top->led = 0;
    top->eval();

    delete top;
    return 0;
}
