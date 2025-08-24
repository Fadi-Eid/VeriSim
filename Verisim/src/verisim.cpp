#include "verisim.hpp"

namespace verisim_ns {

    VeriSim::VeriSim(int argc, char** argv) :   module(new Vverisim()),
                                                moduleIn(*module),
                                                moduleOut(*module) {
    
        Verilated::commandArgs(argc, argv);
        initializeModule();
    }


    VeriSim::~VeriSim() {
        if(isDumpEnabled)
            disableVcdDump();
        delete module;
    }

    void VeriSim::setClockFrequencyHz(uint32_t freq) {
        clock_freq_hz = freq;
        clock_period_ns = 1'000'000'000 / freq;
    }

    /* Call this function every clock toggle */
    void VeriSim::incrementSimTime() {
        sim_time_ns += clock_period_ns / 2;
    }

    uint64_t VeriSim::getSimTime() const {
        return sim_time_ns;
    }

    void VeriSim::restartModule() {
        delete module;
        module = new Vverisim();
        if(isDumpEnabled){
            disableVcdDump();
            enableVcdDump();
        }
        initializeModule();
        sim_time_ns = 0;
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
        module->sevenseg0 = 0;
        module->sevenseg1 = 0;
        module->pwm_b = 0;
        module->pwm_g = 0;
        module->pwm_r = 0;
        module->pwm_gen = 0;
        module->out_bus0 = 0;
        module->out_bus1 = 0;
        module->TX0 = 0;
        module->TX1 = 0;
    }

    void VeriSim::updateModule() {
        module->eval(); // Evaluate the module
        if(isDumpEnabled) {
            vcdDumper->dump(sim_time_ns * 1000);
        }
    }

    void VeriSim::toggleClock() {
        module->clk = !module->clk;
    }

    void VeriSim::enableVcdDump() {
        if(!isDumpEnabled) {
            vcdDumper = new VerilatedVcdC;
            Verilated::traceEverOn(true);
            module->trace(vcdDumper, 99);
            vcdDumper->open("dump.vcd");
            isDumpEnabled = true;
        } 
    }
    void VeriSim::disableVcdDump() {
        if (isDumpEnabled) {
            if (vcdDumper) {
                vcdDumper->close();   // properly close the dump file
                delete vcdDumper;     // free the dumper
                vcdDumper = nullptr;  // clear pointer
            }
            isDumpEnabled = false;
        }
    }

} // namespace verisim