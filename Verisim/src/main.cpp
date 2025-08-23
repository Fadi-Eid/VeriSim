#include "verisim.hpp"
#include "verisimDisplay.hpp"

int main(int argc, char** argv) {
    verisim_ns::VeriSim veriSim(argc, argv);
    veriSim.enableVcdDump();
    veriSim.setClockFrequencyHz(2'000'000);

    for(int i=0; i<1000; i++) {
        veriSim.toggleClock();
        veriSim.incrementSimTime();
        veriSim.updateModule();
    }

}