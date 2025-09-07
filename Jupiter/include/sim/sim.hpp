#ifndef SIM_HPP
#define SIM_HPP

#include "boardState.hpp"
#include "ui.hpp"
#include "module.hpp"

namespace ns_jupiter {

    class Sim {
    private:
        Module module;      // wrapper around the verilog hardware module
        BoardState state;   // reflects the state of the virtual dev board (bridge between ui and sim)
        UI ui;              // updates the state based on user interaction, update the ui based on states
    public:
        Sim();
        void run();  
    };
    
} // namespace ns_jupiter


#endif