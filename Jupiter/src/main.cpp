#include <iostream>
#include "module.hpp"
#include "fileInput.hpp"
#include "logHelper.hpp"

using namespace ns_jupiter;

int main(int argc, char* argv[]) {
    // Instantiate a module
    Module module;
    module.enableDump("dumpster.vcd");
    uint32_t time_stamp = 0;
    
    for(int i=0; i<100; i++) {
        time_stamp += 100;
        module.setBits(Input::Bus0, 0b101, 1);
        module.evaluate();
        module.dump(time_stamp);

        time_stamp += 100;
        module.setBits(Input::Bus0, 0b101, 0);
        module.evaluate();
        module.dump(time_stamp);
    }

    return 0;
}