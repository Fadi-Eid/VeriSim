#include "ui.hpp"
#include <iostream>

namespace ns_jupiter
{

    UI::UI(BoardState &s, int width, int height)
        : state(s), screenWidth(width), screenHeight(height)
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

        // Push buttons box
        buttonsBox = {(float)startX - 30, 170, (float)(spacing * 7) + 60, 80};

        // DIP switches box
        dipsBox = {(float)startX - 30, 280, (float)(spacing * 7) + 60, 80};

        // DIP control buttons (aligned relative to dipsBox)
        dipControls.push_back({{dipsBox.x + dipsBox.width + 20, dipsBox.y, 40, 20}, "FLP", [](BoardState &st)
                               { st.inputs.dips.flip_all = true; }});
        dipControls.push_back({{dipsBox.x + dipsBox.width + 20, dipsBox.y + 25, 40, 20}, "ALL0", [](BoardState &st)
                               { st.inputs.dips.reset_all = true; }});
        dipControls.push_back({{dipsBox.x + dipsBox.width + 20, dipsBox.y + 50, 40, 20}, "ALL1", [](BoardState &st)
                               { st.inputs.dips.set_all = true; }});

        // Switch to disconnect dips
        dipSwitch = {{dipsBox.x + dipsBox.width + 80, dipsBox.y + 20, 50, 30}, "DIP EN"};

        // Invert button for push buttons (aligned next to buttonsBox)
        pushBtnsInvert = {{buttonsBox.x + buttonsBox.width + 20, buttonsBox.y + 30, 60, 20}, "INVERT", [](BoardState &st)
                          { st.inputs.buttons.invert = !st.inputs.buttons.invert; }};

        // Other components
        sevenSeg0 = {{670, 40, 60, 100}, 0};
        sevenSeg1 = {{600, 40, 60, 100}, 1};
        gauge = {100, 400, 400, 30};

        // Input box for in_bus0
        inBus0Box = {{530, 400, 120, 30}, ""}; // (x, y, width, height)
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
        for (SmallButton &ctrl : dipControls)
            ctrl.poll(state);

        dipSwitch.poll(state);

        if (state.inputs.dips.set_all)
        {
            state.inputs.dips.val = 0xFF;
            state.inputs.dips.set_all = false;
        }
        if (state.inputs.dips.reset_all)
        {
            state.inputs.dips.val = 0x00;
            state.inputs.dips.reset_all = false;
        }
        if (state.inputs.dips.flip_all)
        {
            state.inputs.dips.val = ~state.inputs.dips.val;
            state.inputs.dips.flip_all = false;
        }

        pushBtnsInvert.poll(state);

        inBus0Box.poll(state);  // handle typing and update state.inputs.in_bus0
    }

    // render UI based on board state
    void UI::render()
    {
        int spacing = 60;
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

        // Push buttons group border
        DrawRectangleLinesEx(buttonsBox, 2, DARKGRAY);
        DrawText("PUSH BUTTONS", buttonsBox.x + 5, buttonsBox.y - 15, 10, BLACK);

        // DIP group border
        DrawRectangleLinesEx(dipsBox, 2, DARKGRAY);
        DrawText("DIP SWITCHES", dipsBox.x + 5, dipsBox.y - 15, 10, BLACK);

        for (auto &dip : dips)
            dip.draw(state.inputs.dips.val);

        for (auto &ctrl : dipControls)
            ctrl.draw();

        dipSwitch.draw(state);

        pushBtnsInvert.draw();

        inBus0Box.draw();
        DrawText("IN_BUS0", inBus0Box.bounds.x, inBus0Box.bounds.y - 20, 10, BLACK);

        EndDrawing();
    }
} // namespace ns_jupiter
