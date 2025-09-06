#ifndef BOARD_STATE_HPP
#define BOARD_STATE_HPP

#include <cstdint>
#include <string>

namespace ns_jupiter {

    /* --- System-related state --- */
    struct SystemState {
        bool needs_restart = false;
        uint32_t clk_freq_hz = 1'000'000; // 1 MHz
        bool is_running = false;
    };

    /* --- Input-related state --- */
    struct ResetState {
        bool val = false;
    };

    struct ToggleButtonState {
        bool val = false;
    };

    struct ButtonsState {
        uint8_t value = 0;   // 8-bit bus
        bool sw = false;
        bool invert = false;
    };

    struct DipSwitchesState {
        uint8_t value = 0;   // 8-bit bus
        bool sw = false;
        bool set_all = false;
        bool reset_all = false;
        bool flip_all = false;
    };

    struct RXState {
        std::string file_name = "";
        bool sw = false;
    };

    struct InBusState {
        std::string file_name = "";
        bool sw = false;
        bool file_sw = false;
        uint32_t val = 0;   // numeric instead of string
    };
    
    struct Inputs {
        InBusState bus0;
        InBusState bus1;
        RXState rx0;
        RXState rx1;
        DipSwitchesState dips;
        ButtonsState buttons;
        ToggleButtonState toggle_btn;
        ResetState rst;
    };

    /* --- Output-related state --- */
    struct GaugeState {
        uint8_t val = 0; // 0–255
    };
    
    struct TXState {
        std::string file_name = "";
        bool is_hex = false;
        bool is_bin = false;
        bool is_int = false;
    };

    struct LEDsState {
        uint8_t val = 0;
    };

    struct OutBusState {
        std::string file_name = "";
        uint32_t val = 0; // numeric, not string
        bool file_sw = false;
        bool disp_sw = false;
        bool is_hex = false;
        bool is_bin = false;
        bool is_float = false;
        bool is_dec = true;
    };

    struct SevenSegState {
        uint8_t val = 0;
    };

    struct Outputs {
        LEDsState leds;
        SevenSegState sevenSeg0;
        SevenSegState sevenSeg1;
        OutBusState bus0;
        OutBusState bus1;
        TXState tx0;
        TXState tx1;
        GaugeState gauge;
    };
    
    /* --- Composition: the whole board state --- */
    struct BoardState {
        SystemState system;
        Outputs outputs;
        Inputs inputs;
    };

} // namespace ns_jupiter

#endif
