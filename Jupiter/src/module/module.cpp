#include "module.hpp"
#include <stdexcept>
#include <cstring>   // memcpy
#include <string>

namespace ns_jupiter {

    Module::Module() {
        static bool initialized = false;
        if (!initialized) {
            static const char* argv[] = {"sim"};
            Verilated::commandArgs(1, const_cast<char**>(argv));
            initialized = true;
        }
        top = new Vtop();
        initialize();
    };

    Module::~Module() {
        disableDump();
        delete top;
    }

    // ============================
    // Input Setters
    // ============================

    void Module::setInput(Input sig, uint32_t val) {
        switch (sig) {
            case Input::Clk:          top->clk        = val & 1; break;
            case Input::Rst:          top->rst_n      = val & 1; break;
            case Input::ToggleButton: top->toggle_btn = val & 1; break;
            case Input::Rx0:          top->RX0        = val & 1; break;
            case Input::Rx1:          top->RX1        = val & 1; break;
            case Input::Dips:         top->dips       = val & 0xFF; break;
            case Input::Buttons:      top->buttons    = val & 0xFF; break;
            case Input::Bus0:         top->in_bus0    = val; break;
            case Input::Bus1:         top->in_bus1    = val; break;
            default:
                throw std::out_of_range("Invalid Input signal");
        }
    }

    void Module::setBit(Input sig, uint8_t idx, bool val) {
        switch (sig) {
            case Input::Dips:
                if (idx >= 8) throw std::out_of_range("Invalid index for Dips");
                top->dips = (top->dips & ~(1 << idx)) | (val << idx);
                break;
            case Input::Buttons:
                if (idx >= 8) throw std::out_of_range("Invalid index for Buttons");
                top->buttons = (top->buttons & ~(1 << idx)) | (val << idx);
                break;
            case Input::Bus0:
                if (idx >= 32) throw std::out_of_range("Invalid index for Bus0");
                top->in_bus0 = (top->in_bus0 & ~(1u << idx)) | (val << idx);
                break;
            case Input::Bus1:
                if (idx >= 32) throw std::out_of_range("Invalid index for Bus1");
                top->in_bus1 = (top->in_bus1 & ~(1u << idx)) | (val << idx);
                break;
            default:
                throw std::invalid_argument("Signal is not bit-addressable");
        }
    }

    void Module::setBits(Input sig, uint32_t mask, uint32_t val) {
        if(val) val = 1;
        switch (sig) {
            case Input::Dips:
                top->dips = (top->dips & ~mask) | (val * mask);
                break;
            case Input::Buttons:
                top->buttons = (top->buttons & ~mask) | (val * mask);
                break;
            case Input::Bus0:
                top->in_bus0 = (top->in_bus0 & ~mask) | (val * mask);
                break;
            case Input::Bus1:
                top->in_bus1 = (top->in_bus1 & ~mask) | (val * mask);
                break;
            default:
                throw std::invalid_argument("Signal is not bitmaskable");
        }
    }

    void Module::setFloat(Input sig, float f) {
        static_assert(sizeof(float) == 4, "float must be 32 bits");
        uint32_t bits;
        std::memcpy(&bits, &f, sizeof(bits));
        setInput(sig, bits);
    }

    // ============================
    // Input Getters
    // ============================

    uint32_t Module::getInput(Input sig) const {
        switch (sig) {
            case Input::Clk:          return top->clk;
            case Input::Rst:          return top->rst_n;
            case Input::ToggleButton: return top->toggle_btn;
            case Input::Rx0:          return top->RX0;
            case Input::Rx1:          return top->RX1;
            case Input::Dips:         return top->dips;
            case Input::Buttons:      return top->buttons;
            case Input::Bus0:         return top->in_bus0;
            case Input::Bus1:         return top->in_bus1;
            default:
                throw std::out_of_range("Invalid Input signal");
        }
    }

    bool Module::getBit(Input sig, uint8_t idx) const {
        return (getInput(sig) >> idx) & 1;
    }

    // ============================
    // Output Getters
    // ============================

    uint32_t Module::getOutput(Output sig) const {
        switch (sig) {
            case Output::Leds:          return top->leds;
            case Output::PwmRed:        return top->pwm_r;
            case Output::PwmGreen:      return top->pwm_g;
            case Output::PwmBlue:       return top->pwm_b;
            case Output::PwmGeneral:    return top->pwm_gen;
            case Output::Tx0:           return top->TX0;
            case Output::Tx1:           return top->TX1;
            case Output::Bus0:          return top->out_bus0;
            case Output::Bus1:          return top->out_bus1;
            case Output::SevenSegment0: return top->sevenseg0;
            case Output::SevenSegment1: return top->sevenseg1;
            default:
                throw std::out_of_range("Invalid Output signal");
        }
    }

    bool Module::getBit(Output sig, uint8_t idx) const {
        return (getOutput(sig) >> idx) & 1;
    }

    // ============================
    // Lifecycle
    // ============================

    void Module::initialize() {
        top->clk        = 0;
        top->rst_n      = 0;
        top->buttons    = 0;
        top->toggle_btn = 0;
        top->RX0        = 0;
        top->RX1        = 0;
        top->in_bus0    = 0;
        top->in_bus1    = 0;
        top->dips       = 0;

        top->pwm_b     = 0;
        top->pwm_r     = 0;
        top->pwm_g     = 0;
        top->pwm_gen   = 0;
        top->out_bus0  = 0;
        top->out_bus1  = 0;
        top->TX0       = 0;
        top->TX1       = 0;
        top->leds      = 0;
        top->sevenseg0 = 0;
        top->sevenseg1 = 0;
    }

    void Module::evaluate() const {
        top->eval();
    }

    void Module::toggleClock() {
        top->clk = !top->clk;
    }

    void Module::restart() {
        delete top;
        top = new Vtop();
        initialize();
    }

    void Module::enableDump() {
        if(!isDumpEnabled) {
            vcdDumper = new VerilatedVcdC;
            Verilated::traceEverOn(true);
            top->trace(vcdDumper, 99);
            vcdDumper->open("dump.vcd");
            isDumpEnabled = true;
        } 
    }

    void Module::enableDump(std::string fileName) {
        if(!isDumpEnabled) {
            vcdDumper = new VerilatedVcdC;
            Verilated::traceEverOn(true);
            top->trace(vcdDumper, 99);
            vcdDumper->open(fileName.c_str());
            isDumpEnabled = true;
        } 
    }

    void Module::disableDump() {
        if (isDumpEnabled) {
            if (vcdDumper) {
                vcdDumper->close();
                delete vcdDumper;
                vcdDumper = nullptr;
            }
            isDumpEnabled = false;
        }
    }

    void Module::dump(uint32_t timeStamp_ps) const {
        if(isDumpEnabled) {
            vcdDumper->dump(timeStamp_ps);
        }
    }

} // namespace ns_jupiter
