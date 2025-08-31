`BoardState` is just a plain data struct that represents the logical state of your dev board (button presses, DIP positions, buses, outputs…).

`Module` is your Verilator-wrapped simulation model (the "hardware").

`Sim` is the "glue": it coordinates syncing between the UI (BoardState) and the hardware (Module), and handles the simulation loop.

## Flow of the Application

### GUI → BoardState

* The user clicks a button or toggles a DIP switch.
* The `GUI` writes this directly into `BoardState.inputs` (not touching `Module`).

### BoardState → Module

Each simulation tick, `Sim` pushes the current `BoardState.inputs` into the Module.

```c
void Sim::applyInputs() {
    module.setInput(Input::Buttons, boardState.buttons);
    module.setInput(Input::Dips, boardState.dips);
    module.setInput(Input::Rx0, boardState.rx0);
    module.setInput(Input::Bus0, boardState.bus0);  // maybe as float
    // ...
}
```
### Module Evaluate

* Call `module.evaluate()`
* Verilator updates internal signals based on inputs.

### Module → BoardState

After evaluation, read outputs from the `Module` and update `BoardState.outputs`.

```c
void Sim::captureOutputs() {
    boardState.tx0 = module.getOutput(Output::Tx0);
    boardState.leds = module.getOutput(Output::Leds);
    boardState.busOut0 = module.getOutput(Output::Bus0);
    // ...
}
```

### BoardState → GUI

* The GUI queries BoardState to draw the LEDs, TX lines, output buses, etc.
* No GUI code touches the Module directly.


### Advantages 

The GUI code doesn’t need to know anything about `Module` or `Verilator` → it just paints `BoardState`.

The Module doesn’t need to know about `GUI` widgets.

`Sim` is the only layer that understands both worlds.

### Pseudocode Main Loop

```c
int main() {
    Sim sim;
    GUI gui(sim.getBoardState());  // pass ref/pointer to BoardState

    while (!gui.shouldQuit()) {
        gui.pollEvents();               // user interaction updates BoardState
        sim.applyInputs();              // push inputs to Module
        sim.evaluate();                 // run 1 simulation tick
        sim.captureOutputs();           // update BoardState from Module
        gui.render();                   // draw from BoardState
    }
}
```