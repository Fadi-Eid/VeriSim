#ifndef SIM_HPP
#define SIM_HPP

#include "boardState.hpp"
#include "ui.hpp"

namespace ns_jupiter {

    class Sim {
    private:
        BoardState state;
        UI ui;
    public:
        Sim();
        void run();  
    };
    
} // namespace ns_jupiter


#endif