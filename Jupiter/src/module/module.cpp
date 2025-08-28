#include "module.hpp"
#include <stdexcept>

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
        delete top;
    }

    uint32_t Module::getInput(Input sig) const {
        switch (sig) {
            case Input::Clk:          return top->clk;
            case Input::Rst:          return top->rst_n;
            case Input::Dips:         return top->dips;
            case Input::Buttons:      return top->buttons;
            case Input::ToggleButton: return top->toggle_btn;
            case Input::Rx0:          return top->RX0;
            case Input::Rx1:          return top->RX1;
            case Input::Bus0:         return top->in_bus0;
            case Input::Bus1:         return top->in_bus1;
            default:
                throw std::out_of_range("Invalid Input signal");
                return 0;
        }
    }

    void Module::setInput(Input sig, uint32_t val){
        switch (sig) {
            case Input::Clk:          top->clk        = (CData)val;  break;
            case Input::Rst:          top->rst_n      = (CData)val;  break;
            case Input::Dips:         top->dips       = (CData)val;  break;
            case Input::Buttons:      top->buttons    = (CData)val;  break;
            case Input::ToggleButton: top->toggle_btn = (CData)val;  break;
            case Input::Rx0:          top->RX0        = (CData)val;  break;
            case Input::Rx1:          top->RX1        = (CData)val;  break;
            case Input::Bus0:         top->in_bus0    = (IData)val;  break;
            case Input::Bus1:         top->in_bus1    = (IData)val;  break;
            default:
                throw std::out_of_range("Invalid Input signal");
        }
    }

    uint32_t Module::getOutput(Output sig) const {
        switch (sig) {
            case Output::Leds:          return top->leds;
            case Output::PwmBlue:       return top->pwm_b;
            case Output::PwmGreen:      return top->pwm_g;
            case Output::PwmRed:        return top->pwm_r;
            case Output::PwmGeneral:    return top->pwm_gen;
            case Output::Tx0:           return top->TX0;
            case Output::Tx1:           return top->TX1;
            case Output::SevenSegment0: return top->sevenseg0;
            case Output::SevenSegment1: return top->sevenseg1;
            case Output::Bus0:          return top->out_bus0;
            case Output::Bus1:          return top->out_bus1;
            default:
                throw std::out_of_range("Invalid Input signal");
                return 0;
        }
    }

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

} // namespace ns_jupiter