#ifndef UI_HPP
#define UI_HPP

#include "boardState.hpp"
#include "raylib.h"
#include <vector>

namespace ns_jupiter
{
    struct Led
    {
        Rectangle bounds;
        int bitIndex;
        Color onColor = RED;
        Color offColor = DARKGRAY;

        void draw(uint8_t value) const
        {
            bool on = value & (1 << bitIndex);
            DrawCircle(bounds.x + bounds.width / 2, bounds.y + bounds.height / 2,
                       bounds.width / 2, on ? onColor : offColor);
            DrawText(TextFormat("LD%d", bitIndex), bounds.x, bounds.y + bounds.height + 10, 8, BLACK);
        }
    };
    struct PushButton
    {
        Rectangle bounds;
        int bitIndex;

        void poll(BoardState &state) const
        {
            Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, bounds) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                state.inputs.buttons.val &= ~(1 << bitIndex);
            }
            else
            {
                state.inputs.buttons.val |= (1 << bitIndex);
            }
        }

        void draw(uint8_t value) const
        {
            bool pressed = value & (1 << bitIndex);
            DrawRectangleRec(bounds, pressed ? DARKBLUE : LIGHTGRAY);
            DrawText(TextFormat("BT%d", bitIndex), bounds.x, bounds.y + bounds.height + 10, 8, BLACK);
        }
    };

    struct DipSwitch
    {
        Rectangle bounds;
        int bitIndex;

        void poll(BoardState &state) const
        {
            Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                state.inputs.dips.val ^= (1 << bitIndex);
            }
        }

        void draw(uint8_t value) const
        {
            bool on = value & (1 << bitIndex);
            DrawRectangleRec(bounds, on ? GREEN : GRAY);
            DrawText(TextFormat("DP%d", bitIndex), bounds.x, bounds.y + bounds.height + 10, 8, BLACK);
        }
    };

    class UI
    {
    private:
        BoardState &state;
        int screenWidth;
        int screenHeight;
        std::vector<Led> leds;
        std::vector<PushButton> buttons;
        std::vector<DipSwitch> dips;

    public:
        // Constructor
        UI(BoardState &s, int width = 800, int height = 600);

        // Lifecycle
        void init();     // Initialize raylib window, resources
        void shutdown(); // Close window and cleanup

        // Input handling
        void pollInput(); // Update BoardState inputs from mouse/keyboard

        // Rendering
        void render(); // Draw board and outputs to the screen

        // Utility
        bool shouldClose() const; // Check if user wants to exit

        // Combined step
        void update(); // Call pollInput() + render()
    };

}

#endif
