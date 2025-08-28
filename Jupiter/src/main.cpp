#include <iostream>
#include "module.hpp"
#include "fileInput.hpp"
#include "logHelper.hpp"

using namespace ns_jupiter;

int main(int argc, char* argv[]) {
    // Instantiate a module
    Module module;
    module.enableDump("dumpter.vcd");
    uint32_t time_stamp = 0;
    
    for(int i=0; i<100; i++) {
        time_stamp += 100;

        module.setInput(Input::Dips,            !module.getInput(Input::Dips));
        module.setInput(Input::Buttons,         !module.getInput(Input::Buttons));
        module.setInput(Input::Rst,             !module.getInput(Input::Rst));
        module.setInput(Input::Rx0,             !module.getInput(Input::Rx0));
        module.setInput(Input::Rx1,             !module.getInput(Input::Rx1));
        module.setInput(Input::Bus0,            !module.getInput(Input::Bus0));
        module.setInput(Input::Bus1,            !module.getInput(Input::Bus1));
        module.setInput(Input::ToggleButton,    !module.getInput(Input::ToggleButton));

        module.toggleClock();
        module.evaluate();

        std::cout << "____________________ Outputs ____________________" << std::endl;
        printBin(module.getOutput(Output::Leds),            "LEDs    ");
        printBin(module.getOutput(Output::Tx0),             "TX0     ");
        printBin(module.getOutput(Output::Tx1),             "TX1     ");
        printBin(module.getOutput(Output::Bus0),            "BUS0    ");
        printBin(module.getOutput(Output::Bus1),            "BUS1    ");
        printBin(module.getOutput(Output::SevenSegment0),   "SevSeg0 ");
        printBin(module.getOutput(Output::SevenSegment1),   "SevSeg1 ");
        printBin(module.getOutput(Output::PwmBlue),         "PWM_B   ");
        printBin(module.getOutput(Output::PwmRed),          "PWM_R   ");
        printBin(module.getOutput(Output::PwmGreen),        "PWM_G   ");
        printBin(module.getOutput(Output::PwmGeneral),      "PWM_GEN ");
        std::cout << "____________________ Inputs ____________________" << std::endl;
        printBin(module.getInput(Input::Clk),               "Clk     ");
        printBin(module.getInput(Input::Buttons),           "Btns    ");
        printBin(module.getInput(Input::ToggleButton),      "TglBtn  ");
        printBin(module.getInput(Input::Dips),              "Dips    ");
        printBin(module.getInput(Input::Rst),               "Rst     ");
        printBin(module.getInput(Input::Rx0),               "RX0     ");
        printBin(module.getInput(Input::Rx1),               "RX1     ");
        printBin(module.getInput(Input::Bus0),              "BUS0    ");
        printBin(module.getInput(Input::Bus0),              "Bus1    ");
        std::cout << std::endl;

        module.dump(time_stamp);
    }


    return 0;
}