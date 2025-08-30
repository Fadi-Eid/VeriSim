#include <iostream>
#include "module.hpp"
#include "fileInput.hpp"
#include "logHelper.hpp"

using namespace ns_jupiter;

int main(int argc, char* argv[]) {
    // Instantiate a module
    Module module;
    module.enableDump("dumpster.vcd");
    FileIn fileIn("input_file_test.txt");
    std::vector<Pair> pairs = fileIn.getPairs();
    for(auto pair : pairs) {
        module.setInput(Input::Bus0, pair.value);
        module.evaluate();
        module.dump(pair.time_stamp_ns * 1000);
    }

    return 0;
}