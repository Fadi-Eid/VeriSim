#ifndef MODULE_HPP
#define MODULE_HPP

/* This is a wrapper around the hardware */

#include "verilated.h"
#include "Vtop.h"
#include "verilated_vcd_c.h"
#include <cstdint>

namespace ns_jupiter {
    enum class Input {
        Clk, Rst, ToggleButton, Buttons, Dips,
        Rx0, Rx1, Bus0, Bus1
    };

    enum class Output {
        Leds, PwmRed, PwmGreen, PwmBlue, PwmGeneral,
        Tx0, Tx1, Bus0, Bus1, SevenSegment0, SevenSegment1
    };

    class Module {
    public:
        Module();
        ~Module();
    public:
        uint32_t getInput(Input sig) const;
        void     setInput(Input sig, uint32_t val);
        void     resetInput(Input sig) { setInput(sig, 0); }
        void     flipInput(Input sig);
        uint32_t getOutput(Output sig) const;

    private:
        Vtop* top;
    };

} // namespace ns_jupiter

#endif