#include "ui.hpp"
#include <iostream>

namespace ns_jupiter
{

    UI::UI(BoardState &s, int width, int height)
        : state(s), screenWidth(width), screenHeight(height),
          sevenSeg0({{670, 80, 60, 100}, 0}), sevenSeg1({{600,80, 60, 100}, 1}),
          gauge({100, 400, 400, 30})
    {
        leds.reserve(8);
        buttons.reserve(8);
        dips.reserve(8);

        /* Initialize board's layout */
        int startX = 100;
        int spacing = 60;

        // LEDs
        for (int i = 0; i < 8; i++)
        {
            leds.push_back({Rectangle{(float)(startX + i * spacing - 20), 100 - 20, 40, 40}, i});
        }

        // Push buttons
        for (int i = 0; i < 8; i++)
        {
            buttons.push_back({Rectangle{(float)(startX + i * spacing - 20), 200 - 20, 40, 40}, i});
        }

        // DIP switches
        for (int i = 0; i < 8; i++)
        {
            dips.push_back({Rectangle{(float)(startX + i * spacing - 20), 300 - 10, 40, 20}, i});
        }
    }

    // Initialize raylib window, resources
    void UI::init()
    {
        InitWindow(screenWidth, screenHeight, "Jupiter Dev Board");
        SetTargetFPS(60);
        SetWindowState(FLAG_WINDOW_RESIZABLE);
    }

    void UI::shutdown()
    {
        CloseWindow();
    }

    // detect user interactions and update the board state
    void UI::pollInput()
    {
        for (PushButton &btn : buttons)
            btn.poll(state);
        for (DipSwitch &dip : dips)
            dip.poll(state);
    }

    // render UI based on board state
    void UI::render()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (auto &led : leds)
            led.draw(state.outputs.leds.val);
        for (auto &btn : buttons)
            btn.draw(state.inputs.buttons.val);
        for (auto &dip : dips)
            dip.draw(state.inputs.dips.val);
        
        sevenSeg0.draw(state.outputs.sevenSeg0.val);
        sevenSeg1.draw(state.outputs.sevenSeg1.val);

        gauge.draw(state.outputs.gauge.val);

        EndDrawing();
    }
} // namespace ns_jupiter
