#include "sim.hpp"

namespace ns_jupiter {

    Sim::Sim() : state(), module(), ui(state, 800, 600) {}

    void Sim::run() {
        ui.init();

        while (!WindowShouldClose()) {
            ui.pollInput();

            // check the board state and update module inputs accordingly

            // read from files

            // evaluate module

            // extract module outputs and update board state

            // write to files

            // --- Render everything (inputs and outputs change) ---
            ui.render();
        }

        ui.shutdown();
    }

} // namespace ns_jupiter
