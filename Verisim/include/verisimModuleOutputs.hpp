#ifndef VERISIM_MODULE_OUTPUTS_HPP
#define VERISIM_MODULE_OUTPUTS_HPP

#include "verilated.h"
#include "Vverisim.h"

namespace verisim_ns {
    enum MODULE_OUTPUTS {
        leds, pwnGreen, pwmRed, pwmBlue, pwmGeneral, tx0, tx1, bus0, bus1
    };

    class VeriSimModuleOutputs {
    public:
        VeriSimModuleOutputs(Vverisim& module);
        ~VeriSimModuleOutputs();

        /* Input files related functions */
        void connectFileToOutput(MODULE_OUTPUTS input);
        void disconnectFileFromOutput(MODULE_OUTPUTS input);
        void updateFileConnectedOutputs();

        /* Getters for Module Outputs */
        CData getOutput_leds();
        CData getOutput_led_x(CData idx);

        CData getOutput_pwmRed();
        CData getOutput_pwmGreen();
        CData getOutput_pwmBlue();
        CData getOutput_pwmGeneral();

        CData getOutput_tx0();
        CData getOutput_tx1();

        IData getOutput_bus0();
        CData getOutput_bus0_x(CData idx);
        float getOutput_bus0_float();
        int   getOutput_bus0_int();
        char  getOutput_bus0_char();

        IData getOutput_bus1();
        CData getOutput_bus1_x(CData idx);
        float getOutput_bus1_float();
        int   getOutput_bus1_int();
        char  getOutput_bus1_char();

        CData getOutput_sevenSegment0();
        CData getOutput_sevenSegment0_x(CData idx);

        CData getOutput_sevenSegment1();
        CData getOutput_sevenSegment1_x(CData idx);

    private:
        Vverisim* module;
    };
}


#endif