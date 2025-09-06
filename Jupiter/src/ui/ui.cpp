#include "ui.hpp"

namespace ns_jupiter {

    UI::UI(BoardState& s, int width, int height) 
        : state(s), screenWidth(width), screenHeight(height) {
    }

    // Initialize raylib window, resources
    void UI::init() {
        InitWindow(screenWidth, screenHeight, "Jupiter Dev Board");
        SetTargetFPS(60);

        // Customize window
        SetWindowState(FLAG_WINDOW_RESIZABLE);
        // SetWindowIcon(LoadImage("icon.png"));
        // Load resources here (textures, fonts, etc.)
    }

    void UI::shutdown() {
        CloseWindow();
    }

    void UI::render() {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Example: draw LEDs
        if (state.outputs.leds.val & 0x1)
            DrawCircle(100, 100, 20, RED);
        else
            DrawCircle(100, 100, 20, DARKGRAY);

        EndDrawing();
    }

} // namespace ns_jupiter