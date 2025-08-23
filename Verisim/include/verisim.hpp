#ifndef VERISIM_HPP
#define VERISIM_HPP

#include "verilated.h"

namespace verisim {

    class VeriSim {
    public:
        VeriSim();
        ~VeriSim();

        /* Action functions */
        void updateModule();
        void toggleClock();
        void GTKWaveDump();

        /* Getters for Module Inputs */
        CData getInput_clk();
        CData getInput_rst();
        CData getInput_toggleButton();
        CData getInput_buttons();
        CData getInput_button_x();
        CData getInput_dips();
        CData getInput_dip_x();
        CData getInput_rx0();
        CData getInput_rx1();
        IData getInput_bus0();
        CData getInput_bus0_x();
        IData getInput_bus1();
        CData getInput_bus1_x();

        /* Getters for Module Outputs */
        CData getOutput_leds();
        CData getOutputs_led_x();
        CData getOuptut_pwmRed();
        CData getOutput_pwmGreen();
        CData getOutput_pwmBlue();
        CData getOutput_pwmGeneral();
        CData getOuput_tx0();
        CData getOutput_tx1();
        IData getOutput_bus0();
        float getOutputs_bus0_float();
        int   getOutputs_bus0_int();
        char  getOutputs_bus0_char();
        IData getOutput_bus1();
        float getOutputs_bus1_float();
        int   getOutputs_bus1_int();
        char  getOutputs_bus1_char();
        CData getOutput_sevenSegment0();
        CData getOutput_sevenSegment0_x();
        CData getOutput_sevenSegment1();
        CData getOutput_sevenSegment1_x();

        /* Setters for Module Inputs */
        void setInput_clk(CData);
        void setInput_rst(CData);
        void setInput_toggleButton(CData);
        void setInput_buttons(CData);
        void setInput_button_x(CData);
        void setInput_dips(CData);
        void setInput_dip_x(CData);
        void setInput_rx0(CData);
        void setInput_rx1(CData);
        void setInput_bus0(IData);
        void setInput_bus0_x(CData);
        void setInput_bus1(IData);
        void setInput_bus1_x(CData);
    };
}



#endif