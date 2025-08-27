#include "module.hpp"

namespace ns_jupiter {

    Module::Module() {
        static bool initialized = false;
        if (!initialized) {
            static const char* argv[] = {"sim"};
            Verilated::commandArgs(1, const_cast<char**>(argv));
            initialized = true;
        }
        top = new Vtop();
    };

    Module::~Module() {
        delete top;
    }


} // namespace ns_jupiter