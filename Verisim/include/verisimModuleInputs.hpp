#ifndef VERISIM_MODULE_INPUTS_HPP
#define VERISIM_MODULE_INPUTS_HPP

#include "verilated.h"
#include "Vverisim.h"

namespace verisim_ns {
    enum MODULE_INPUTS {
        clk, rst_n, dips, buttons, toggle_button, rx0, rx1, in_bus0, in_bus1
    };

    class VeriSimModuleInputs {
    public:
        VeriSimModuleInputs(Vverisim& module);
        ~VeriSimModuleInputs();

        /* Input files related functions */
        void connectFileToInput(MODULE_INPUTS input);
        void disconnectFileFromInput(MODULE_INPUTS input);
        void updateFileConnectedInputs();

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
    
    private:
        Vverisim* module;
    };
}


#endif