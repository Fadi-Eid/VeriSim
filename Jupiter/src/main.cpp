#include <iostream>
#include <vector>
#include "module.hpp"
#include "fileInput.hpp"
#include "fileOutput.hpp"
#include "logHelper.hpp"
#include "raylib.h"

using namespace ns_jupiter;



int main(int argc, char* argv[]) {
    // Instantiate module
    Module module;

    // Enable VCD dump (viewable in GTKWave)
    module.enableDump("dumpster.vcd");

    // Files IOs
    FileIn fileIn("input_file_test.txt");
    FileOut fileOut("output_file_test.txt");

    // Load time stamp / value pairs from input file
    std::vector<Pair> pairs = fileIn.getPairs();

    for(auto pair : pairs) {
        module.setInput(Input::Bus0, pair.value);
        module.evaluate();
        module.dump(pair.time_stamp_ns);
        fileOut.append(pair.time_stamp_ns, pair.value, OutputFormat::HEX);
    }

    InitWindow(800, 450, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
  
    return 0;
}
