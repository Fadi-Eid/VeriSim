#ifndef VERISIM_HPP
#define VERISIM_HPP

#include "verilated.h"
#include "Vverisim.h"
#include "verilated_vcd_c.h"
#include "verisimModuleInputs.hpp"
#include "verisimModuleOutputs.hpp"

namespace verisim_ns {
    class VeriSim {
    public:
        VeriSim(int argc, char** argv);
        ~VeriSim();

        /* Main module functions */
        void restartModule();
        void updateModule();
        void initializeModule();
        void toggleClock();
        void enableVcdDump();
        void disableVcdDump();
        void incrementSimTime();
        void setClockFrequencyHz(uint32_t freq);
        uint64_t getSimTime() const;       
    
    private:
        Vverisim* module;
        VeriSimModuleInputs moduleIn;
        VeriSimModuleOutputs moduleOut;
        bool isDumpEnabled = false;
        VerilatedVcdC* vcdDumper;
        uint64_t sim_time_ns = 0;
        uint32_t clock_freq_hz = 1'000'000; // 1 MHz 
        uint32_t clock_period_ns = 1000; // 1us
    };
} // namespace verisim_ns

#endif