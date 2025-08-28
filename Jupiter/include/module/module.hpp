#ifndef MODULE_HPP
#define MODULE_HPP

/* This is a wrapper around the hardware */

#include "verilated.h"
#include "Vtop.h"
#include "verilated_vcd_c.h"
#include <cstdint>
#include <string>

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
        void     evaluate() const;
        void     toggleClock();
        void     restart();
        void     enableDump();
        void     enableDump(std::string fileName);
        void     disableDump();
        void     dump(uint32_t timeStamp_ps) const;
        uint32_t getInput(Input sig) const;
        void     setInput(Input sig, uint32_t val);
        uint32_t getOutput(Output sig) const;
    private:
        void initialize();
    private:
        Vtop* top;
        VerilatedVcdC* vcdDumper;
        bool isDumpEnabled = false;
    };

} // namespace ns_jupiter

#endif