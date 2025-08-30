#ifndef MODULE_HPP
#define MODULE_HPP

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

        // Simulation control
        void evaluate() const;
        void toggleClock();
        void restart();
        void enableDump();
        void enableDump(std::string fileName);
        void disableDump();
        void dump(uint32_t timeStamp_ps) const;

        // === Input setters ===
        void setInput(Input sig, uint32_t val);              // full wire/bus
        void setBit(Input sig, uint8_t idx, bool val);       // single bit
        void setBits(Input sig, uint32_t mask, uint32_t val);// multiple bits (masked)
        void setFloat(Input sig, float f);                   // float as raw bits

        // === Input getters ===
        uint32_t getInput(Input sig) const;
        bool getBit(Input sig, uint8_t idx) const;

        // === Output getters ===
        uint32_t getOutput(Output sig) const;
        bool getBit(Output sig, uint8_t idx) const;

    private:
        void initialize();

        Vtop* top;
        VerilatedVcdC* vcdDumper;
        bool isDumpEnabled = false;
    };

} // namespace ns_jupiter

#endif
