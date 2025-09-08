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

    struct SevenSegment
    {
        Rectangle bounds;
        int bitIndex;                            // Which 4-bit slice of state.inputs/outputs controls it
        Color onColor = (Color){180, 0, 0, 255}; // darker red
        Color offColor = (Color){80, 0, 0, 30};  // dim red, translucent

        // Segment encoding for hexadecimal 0-F
        static uint8_t digitToSegments(uint8_t digit)
        {
            static const uint8_t map[16] = {
                0b0111111, // 0
                0b0000110, // 1
                0b1011011, // 2
                0b1001111, // 3
                0b1100110, // 4
                0b1101101, // 5
                0b1111101, // 6
                0b0000111, // 7
                0b1111111, // 8
                0b1101111, // 9
                0b1110111, // A
                0b1111100, // b
                0b0111001, // C
                0b1011110, // d
                0b1111001, // E
                0b1110001  // F
            };
            return map[digit & 0xF];
        }

        void draw(uint8_t segs) const
        {
            // segs is active-low from Verilog, so invert it
            segs = ~segs;

            float x = bounds.x;
            float y = bounds.y;
            float w = bounds.width;
            float h = bounds.height;
            float t = w * 0.15f;    // thickness of a segment
            float roundness = 0.4f; // rounded corners

            auto drawSegment = [&](Rectangle r, bool on)
            {
                if (on)
                {
                    // Glow (slightly bigger, faded)
                    DrawRectangleRounded(
                        {r.x - 2, r.y - 2, r.width + 4, r.height + 4},
                        roundness, 6, Fade(onColor, 0.3f));
                    // Core
                    DrawRectangleRounded(r, roundness, 6, onColor);
                }
                else
                {
                    DrawRectangleRounded(r, roundness, 6, offColor);
                }
            };

            // Horizontal segments: A (bit0), G (bit6), D (bit3)
            drawSegment({x + t, y, w - 2 * t, t}, segs & (1 << 0));                 // A
            drawSegment({x + t, y + h / 2 - t / 2, w - 2 * t, t}, segs & (1 << 6)); // G
            drawSegment({x + t, y + h - t, w - 2 * t, t}, segs & (1 << 3));         // D

            // Vertical segments: F (bit5), B (bit1), E (bit4), C (bit2)
            drawSegment({x, y + t, t, h / 2 - t}, segs & (1 << 5));             // F
            drawSegment({x + w - t, y + t, t, h / 2 - t}, segs & (1 << 1));     // B
            drawSegment({x, y + h / 2, t, h / 2 - t}, segs & (1 << 4));         // E
            drawSegment({x + w - t, y + h / 2, t, h / 2 - t}, segs & (1 << 2)); // C

            // --- Label ---
            DrawText(TextFormat("7S%d", bitIndex),
                     x + w / 2 - MeasureText(TextFormat("7S%d", bitIndex), 10) / 2,
                     y + h + 8, 10, BLACK);
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
        SevenSegment sevenSeg0;
        SevenSegment sevenSeg1;

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
