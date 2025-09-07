#include "ui.hpp"

namespace ns_jupiter
{

    UI::UI(BoardState &s, int width, int height)
        : state(s), screenWidth(width), screenHeight(height)
    {
    }

    // Initialize raylib window, resources
    void UI::init()
    {
        InitWindow(screenWidth, screenHeight, "Jupiter Dev Board");
        SetTargetFPS(60);

        // Customize window
        SetWindowState(FLAG_WINDOW_RESIZABLE);
        // SetWindowIcon(LoadImage("icon.png"));
        // Load resources here (textures, fonts, etc.)
    }

    void UI::shutdown()
    {
        CloseWindow();
    }

    // detect user interactions and update the board state
    void UI::pollInput()
    {
        Vector2 mouse = GetMousePosition();

        // --- Push Buttons (momentary) ---
        for (int i = 0; i < 8; i++)
        {
            Rectangle btnRect = {(float)(100 + i * 60 - 20), (float)(200 - 20), 40, 40};

            if (CheckCollisionPointRec(mouse, btnRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                // pressed = 0
                state.inputs.buttons.val &= ~(1 << i);
            }
            else
            {
                // released = 1
                state.inputs.buttons.val |= (1 << i);
            }
        }

        // --- DIP Switches (toggle when clicked) ---
        for (int i = 0; i < 8; i++)
        {
            Rectangle swRect = {(float)(100 + i * 60 - 20), (float)(300 - 10), 40, 20};
            if (CheckCollisionPointRec(mouse, swRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                state.inputs.dips.val ^= (1 << i);
            }
        }

        // --- Control Buttons ---
        int ctrlY = 450;
        int ctrlX = 100;
        int spacing = 120;
        int w = 110, h = 30;

        Rectangle invertLedsBtn = {(float)ctrlX, (float)ctrlY, (float)w, (float)h};
        Rectangle dipsAll1Btn = {(float)(ctrlX + spacing), (float)ctrlY, (float)w, (float)h};
        Rectangle dipsAll0Btn = {(float)(ctrlX + 2 * spacing), (float)ctrlY, (float)w, (float)h};
        Rectangle dipsInvertBtn = {(float)(ctrlX + 3 * spacing), (float)ctrlY, (float)w, (float)h};
        Rectangle invertBtnsBtn = {(float)(ctrlX + 4 * spacing), (float)ctrlY, (float)w, (float)h};

        if (CheckCollisionPointRec(mouse, invertLedsBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            state.outputs.leds.val ^= 0xFF;
        }
        if (CheckCollisionPointRec(mouse, dipsAll1Btn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            state.inputs.dips.val = 0xFF;
        }
        if (CheckCollisionPointRec(mouse, dipsAll0Btn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            state.inputs.dips.val = 0x00;
        }
        if (CheckCollisionPointRec(mouse, dipsInvertBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            state.inputs.dips.val ^= 0xFF;
        }
        if (CheckCollisionPointRec(mouse, invertBtnsBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            state.inputs.buttons.val ^= 0xFF;
        }
    }

    // render UI based on board state
    void UI::render()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Layout parameters
        int startX = 100;
        int startY = 100;
        int spacing = 60;

        // --- LEDs ---
        for (int i = 0; i < 8; i++)
        {
            int x = startX + i * spacing;
            int y = startY;

            bool ledOn = state.outputs.leds.val & (1 << i);
            DrawCircle(x, y, 20, ledOn ? RED : DARKGRAY);
            DrawText(TextFormat("LD%d", i), x - 25, y + 30, 8, BLACK);
        }

        // --- Push Buttons ---
        for (int i = 0; i < 8; i++)
        {
            int x = startX + i * spacing;
            int y = startY + 100;

            bool pressed = state.inputs.buttons.val & (1 << i);
            DrawRectangle(x - 20, y - 20, 40, 40, pressed ? DARKBLUE : LIGHTGRAY);
            DrawText(TextFormat("BT%d", i), x - 25, y + 30, 8, BLACK);
        }

        // --- DIP Switches ---
        for (int i = 0; i < 8; i++)
        {
            int x = startX + i * spacing;
            int y = startY + 200;

            bool on = state.inputs.dips.val & (1 << i);
            DrawRectangle(x - 20, y - 10, 40, 20, on ? GREEN : GRAY);
            DrawText(TextFormat("DP%d", i), x - 25, y + 30, 8, BLACK);
        }

        // --- Control Buttons ---
        int ctrlY = 450;
        int ctrlX = 100;
        spacing = 120;
        int w = 110, h = 30;

        DrawRectangle(ctrlX, ctrlY, w, h, LIGHTGRAY);
        DrawText("Invert LEDs", ctrlX + 10, ctrlY + 8, 10, BLACK);

        DrawRectangle(ctrlX + spacing, ctrlY, w, h, LIGHTGRAY);
        DrawText("DIPs = 1", ctrlX + spacing + 15, ctrlY + 8, 10, BLACK);

        DrawRectangle(ctrlX + 2 * spacing, ctrlY, w, h, LIGHTGRAY);
        DrawText("DIPs = 0", ctrlX + 2 * spacing + 15, ctrlY + 8, 10, BLACK);

        DrawRectangle(ctrlX + 3 * spacing, ctrlY, w, h, LIGHTGRAY);
        DrawText("Invert DIPs", ctrlX + 3 * spacing + 10, ctrlY + 8, 10, BLACK);

        DrawRectangle(ctrlX + 4 * spacing, ctrlY, w, h, LIGHTGRAY);
        DrawText("Invert BTN", ctrlX + 4 * spacing + 10, ctrlY + 8, 10, BLACK);

        EndDrawing();
    }

} // namespace ns_jupiter
