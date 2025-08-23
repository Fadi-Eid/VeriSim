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
        CData getInput_button_x(CData idx);

        CData getInput_dips();
        CData getInput_dip_x(CData idx);

        CData getInput_rx0();
        CData getInput_rx1();

        IData getInput_bus0();
        CData getInput_bus0_x(CData idx);

        IData getInput_bus1();
        CData getInput_bus1_x(CData idx);

        /* Getters for Module Outputs */
        CData getOutput_leds();
        CData getOutputs_led_x(CData idx);

        CData getOuptut_pwmRed();
        CData getOutput_pwmGreen();
        CData getOutput_pwmBlue();
        CData getOutput_pwmGeneral();

        CData getOuput_tx0();
        CData getOutput_tx1();

        IData getOutput_bus0();
        CData getOutput_bus0_x(CData idx);
        float getOutputs_bus0_float();
        int   getOutputs_bus0_int();
        char  getOutputs_bus0_char();

        IData getOutput_bus1();
        CData getOutput_bus1_x(CData idx);
        float getOutputs_bus1_float();
        int   getOutputs_bus1_int();
        char  getOutputs_bus1_char();

        CData getOutput_sevenSegment0();
        CData getOutput_sevenSegment0_x(CData idx);

        CData getOutput_sevenSegment1();
        CData getOutput_sevenSegment1_x(CData idx);

        /* Modifier for Module Inputs */
        void setInput_clk();
        void setInput_rst();
        void setInput_toggleButton();
        void setInput_buttons();
        void setInput_button_x(CData idx);
        void setInput_dips();
        void setInput_dip_x(CData idx);
        void setInput_rx0();
        void setInput_rx1();
        void setInput_bus0();
        void setInput_bus0_x(CData idx);
        void setInput_bus1();
        void setInput_bus1_x(CData idx);

        void resetInput_clk();
        void resetInput_rst();
        void resetInput_toggleButton();
        void resetInput_buttons();
        void resetInput_button_x(CData idx);
        void resetInput_dips();
        void resetInput_dip_x(CData idx);
        void resetInput_rx0();
        void resetInput_rx1();
        void resetInput_bus0();
        void resetInput_bus0_x(CData idx);
        void resetInput_bus1();
        void resetInput_bus1_x(CData idx);

        void flipInput_clk();
        void flipInput_rst();
        void flipInput_toggleButton();
        void flipInput_buttons();
        void flipInput_button_x(CData idx);
        void flipInput_dips();
        void flipInput_dip_x(CData idx);
        void flipInput_rx0();
        void flipInput_rx1();
        void flipInput_bus0();
        void flipInput_bus0_x(CData idx);
        void flipInput_bus1();
        void flipInput_bus1_x(CData idx);
    };
}



#endif