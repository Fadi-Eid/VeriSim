#include "verisim.hpp"
#include "verisimFilesIO.hpp"
#include "verisimDisplay.hpp"
#include <vector>

int main(int argc, char** argv) {
    verisim_ns::VeriSim veriSim(argc, argv);
    veriSim.enableVcdDump();
    veriSim.setClockFrequencyHz(2'000'000);

    verisim_ns::VeriSimFileIn veriSimInFile("input_file.txt");
    std::vector<verisim_ns::Pair> pairs = veriSimInFile.getPairs();

    for(auto pair : pairs) {
        std::cout << "time stamp: " << pair.time_stamp_ns << " | value: " << (int)pair.value << std::endl;
    }

    for(int i=0; i<1000; i++) {
        veriSim.toggleClock();
        veriSim.incrementSimTime();
        veriSim.updateModule();
    }

}