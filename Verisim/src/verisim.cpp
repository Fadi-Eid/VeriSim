#include "verisim.hpp"
#include "verisimHelper.hpp"

namespace verisim_ns {

VeriSim::VeriSim(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    module = new Vverisim();
    initializeModule();
}

VeriSim::~VeriSim() {
    delete module;
}

void VeriSim::restartModule() {
    delete module;
    module = new Vverisim();
    initializeModule();
}

void VeriSim::initializeModule() {
    // Initialize inputs / outputs to 0
    module->clk = 0;
    module->rst_n = 0;
    module->dips = 0;
    module->buttons = 0;
    module->toggle_btn = 0;
    module->in_bus0 = 0;
    module->in_bus1 = 0;
    module->RX0 = 0;
    module->RX1 = 0;

    module->leds = 0;
    module->sevenseg = 0;
    module->pwm_b = 0;
    module->pwm_g = 0;
    module->pwm_r = 0;
    module->pwm_gen = 0;
    module->out_bus0 = 0;
    module->out_bus1 = 0;
    module->TX0 = 0;
    module->TX1 = 0;
}


} // namespace verisim