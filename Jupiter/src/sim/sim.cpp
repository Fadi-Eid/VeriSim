#include "sim.hpp"

namespace ns_jupiter {
    Sim::Sim() : state(), ui(state, 800, 600) {}

    void Sim::run() {
        ui.init();

        while (!WindowShouldClose()) {
            // For testing, toggle LED output every frame
            state.outputs.leds.val ^= 0x1;

            ui.render();
        }

        ui.shutdown();
    }

} // namespace ns_jupiter