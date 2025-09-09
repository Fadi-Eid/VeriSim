#include "sim.hpp"
#include <chrono>
#include <thread>
#include <iostream>

namespace ns_jupiter
{

    Sim::Sim() : state(), module(), ui(state, 800, 600) {}

    void Sim::run()
    {
        ui.init();

        const double clk_period_s = 1.0 / 10e6; // 10 MHz
        const double frame_time_s = 1.0 / 60.0; // 60 FPS

        while (!WindowShouldClose())
        {
            auto frame_start = std::chrono::high_resolution_clock::now();

            // Run clocks until next UI frame
            double t_frame = 0.0;
            while (t_frame < frame_time_s)
            {
                module.toggleClock();
                module.evaluate();
                t_frame += clk_period_s/2.0;
            }

            // Update UI, module inputs/outputs
            ui.pollInput();

            uint8_t btnVal = state.inputs.buttons.val;
            if (state.inputs.buttons.invert)
                btnVal = ~btnVal;
            module.setInput(Input::Buttons, btnVal);

            module.setInput(Input::Bus0, state.inputs.bus0.val);
            std::cout << (int)state.inputs.bus0.val << std::endl;

            if(state.inputs.dips.sw)
                module.setInput(Input::Dips, state.inputs.dips.val);
            else
                module.setInput(Input::Dips, 0);

            state.outputs.sevenSeg0.val = module.getOutput(Output::SevenSegment0);
            state.outputs.sevenSeg1.val = module.getOutput(Output::SevenSegment1);
            state.outputs.leds.val =      module.getOutput(Output::Leds);
            state.outputs.gauge.val =     module.getOutput(Output::Gauge);

            ui.render();

            // Calculate elapsed time
            auto frame_end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = frame_end - frame_start;

            // Sleep remaining time if needed
            if (elapsed.count() < frame_time_s)
            {
                // std::cout << "module is in sync" << std::endl;
                std::this_thread::sleep_for(std::chrono::duration<double>(frame_time_s - elapsed.count()));
            }
            else
            {
                std::cout << "module is behind" << std::endl;
            }
        }

        ui.shutdown();
    }

} // namespace ns_jupiter
