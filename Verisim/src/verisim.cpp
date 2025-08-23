#include "verisim.hpp"
#include "verisimHelper.hpp"

namespace verisim_ns {

VeriSim::VeriSim(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    module = new Vverisim();
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

void VeriSim::increaseSimTime() {
    sim_time_ns += clock_period_ns;
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

/* Getters for Module Inputs */
CData VeriSim::getInput_clk() {
    return module->clk;
}
CData VeriSim::getInput_rst() {
    return module->rst_n;
}
CData VeriSim::getInput_toggleButton() {
    return module->toggle_btn;
}
CData VeriSim::getInput_buttons() {
    return module->buttons;
}
CData VeriSim::getInput_dips() {
    return module->dips;
}
CData VeriSim::getInput_rx0() {
    return module->RX0;
}
CData VeriSim::getInput_rx1() {
    return module->RX1;
}
IData VeriSim::getInput_bus0() {
    return module->in_bus0;
}
IData VeriSim::getInput_bus1() {
    return module->in_bus1;
}

/* Getter for Module Outputs */
CData VeriSim::getOutput_leds() {
    return module->leds;
}
CData VeriSim::getOutput_sevenSegment0() {
    return module->sevenseg0;
}
CData VeriSim::getOutput_sevenSegment1() {
    return module->sevenseg1;
}
CData VeriSim::getOutput_pwmBlue() {
    return module->pwm_b;
}
CData VeriSim::getOutput_pwmGreen() {
    return module->pwm_g;
}
CData VeriSim::getOutput_pwmRed() {
    return module->pwm_r;
}
CData VeriSim::getOutput_pwmGeneral() {
    return module->pwm_gen;
}
CData VeriSim::getOutput_tx0() {
    return module->TX0;
}
CData VeriSim::getOutput_tx1() {
    return module->TX1;
}
IData VeriSim::getOutput_bus0() {
    return module->out_bus0;
}
IData VeriSim::getOutput_bus1() {
    return module->out_bus1;
}

/* Special getters for the inputs */
CData VeriSim::getInput_button_x(CData idx) {
    return helper::getBit(module->buttons, idx);
}
CData VeriSim::getInput_bus0_x(CData idx) {
    return helper::getBit(module->in_bus0, idx);
}
CData VeriSim::getInput_bus1_x(CData idx) {
    return helper::getBit(module->in_bus1, idx);
}
CData VeriSim::getInput_dip_x(CData idx) {
    return helper::getBit(module->dips, idx);
}

/* Special getters for the outputs */
CData VeriSim::getOutput_led_x(CData idx) {
    return helper::getBit(module->leds, idx);
}
CData VeriSim::getOutput_bus0_x(CData idx) {
    return helper::getBit(module->out_bus0, idx);
}
CData VeriSim::getOutput_bus1_x(CData idx) {
    return helper::getBit(module->out_bus1, idx);
}
CData VeriSim::getOutput_sevenSegment0_x(CData idx) {
    return helper::getBit(module->sevenseg0, idx);
}
CData VeriSim::getOutput_sevenSegment1_x(CData idx) {
    return helper::getBit(module->sevenseg1, idx);
}

/* Modifier for Module Inputs */
void VeriSim::setInput_clk() {
    helper::setData(module->clk);
}
void VeriSim::setInput_rst() {
    helper::setData(module->rst_n);
}
void VeriSim::setInput_toggleButton() {
    helper::setData(module->toggle_btn);
}
void VeriSim::setInput_rx0() {
    helper::setData(module->RX0);
}
void VeriSim::setInput_rx1() {
    helper::setData(module->RX1);
}
void VeriSim::setInput_buttons() {
    helper::setData(module->buttons);
}
void VeriSim::setInput_dips() {
    helper::setData(module->dips);
}
void VeriSim::setInput_bus0() {
    helper::setData(module->in_bus0);
}
void VeriSim::setInput_bus1() {
    helper::setData(module->in_bus1);
}
void VeriSim::setInput_button_x(CData idx) {
    helper::setBit(module->buttons, idx);
}
void VeriSim::setInput_dip_x(CData idx) {
    helper::setBit(module->dips, idx);
}
void VeriSim::setInput_bus0_x(CData idx) {
    helper::setBit(module->in_bus0, idx);
}
void VeriSim::setInput_bus1_x(CData idx) {
    helper::setBit(module->in_bus1, idx);
}
////////////////////////
void VeriSim::resetInput_clk() {
    helper::resetData(module->clk);
}
void VeriSim::resetInput_rst() {
    helper::resetData(module->rst_n);
}
void VeriSim::resetInput_toggleButton() {
    helper::resetData(module->toggle_btn);
}
void VeriSim::resetInput_rx0() {
    helper::resetData(module->RX0);
}
void VeriSim::resetInput_rx1() {
    helper::resetData(module->RX1);
}
void VeriSim::resetInput_buttons() {
    helper::resetData(module->buttons);
}
void VeriSim::resetInput_dips() {
    helper::resetData(module->dips);
}
void VeriSim::resetInput_bus0() {
    helper::resetData(module->in_bus0);
}
void VeriSim::resetInput_bus1() {
    helper::resetData(module->in_bus1);
}
void VeriSim::resetInput_button_x(CData idx) {
    helper::resetBit(module->buttons, idx);
}
void VeriSim::resetInput_dip_x(CData idx) {
    helper::resetBit(module->dips, idx);
}
void VeriSim::resetInput_bus0_x(CData idx) {
    helper::resetBit(module->in_bus0, idx);
}
void VeriSim::resetInput_bus1_x(CData idx) {
    helper::resetBit(module->in_bus1, idx);
}
////////////////////////
void VeriSim::flipInput_clk() {
    helper::flipData(module->clk);
}
void VeriSim::flipInput_rst() {
    helper::flipData(module->rst_n);
}
void VeriSim::flipInput_toggleButton() {
    helper::flipData(module->toggle_btn);
}
void VeriSim::flipInput_rx0() {
    helper::flipData(module->RX0);
}
void VeriSim::flipInput_rx1() {
    helper::flipData(module->RX1);
}
void VeriSim::flipInput_buttons() {
    helper::flipData(module->buttons);
}
void VeriSim::flipInput_dips() {
    helper::flipData(module->dips);
}
void VeriSim::flipInput_bus0() {
    helper::flipData(module->in_bus0);
}
void VeriSim::flipInput_bus1() {
    helper::flipData(module->in_bus1);
}
void VeriSim::flipInput_button_x(CData idx) {
    helper::flipBit(module->buttons, idx);
}
void VeriSim::flipInput_dip_x(CData idx) {
    helper::flipBit(module->dips, idx);
}
void VeriSim::flipInput_bus0_x(CData idx) {
    helper::flipBit(module->in_bus0, idx);
}
void VeriSim::flipInput_bus1_x(CData idx) {
    helper::flipBit(module->in_bus1, idx);
}
//////////////////////////////
int VeriSim::getOutput_bus0_int() {
    return static_cast<int>(module->in_bus0);
}
char VeriSim::getOutput_bus0_char() {
    return static_cast<char>(module->in_bus0 & 0xFF);
}
float VeriSim::getOutput_bus0_float() {
    float f;
    std::memcpy(&f, &module->in_bus0, sizeof(f));
    return f;
}
int VeriSim::getOutput_bus1_int() {
    return static_cast<int>(module->in_bus1);
}
char VeriSim::getOutput_bus1_char() {
    return static_cast<char>(module->in_bus1 & 0xFF);
}
float VeriSim::getOutput_bus1_float() {
    float f;
    std::memcpy(&f, &module->in_bus1, sizeof(f));
    return f;
}

} // namespace verisim