#ifndef UI_HPP
#define UI_HPP

#include "boardState.hpp"
#include "raylib.h"

namespace ns_jupiter {

    class UI {
    private:
        BoardState& state;

        // Example: window dimensions
        int screenWidth;
        int screenHeight;

    public:
        // Constructor
        UI(BoardState& s, int width = 800, int height = 600);

        // Lifecycle
        void init();       // Initialize raylib window, resources
        void shutdown();   // Close window and cleanup

        // Input handling
        void pollInput();  // Update BoardState inputs from mouse/keyboard

        // Rendering
        void render();     // Draw board and outputs to the screen

        // Utility
        bool shouldClose() const; // Check if user wants to exit

        // Combined step
        void update();     // Call pollInput() + render()
    };

}

#endif
