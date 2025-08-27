// Simple IO fabric demo with dummy logic
// Verilog-2001 (synthesizable)

module top (
    input  wire        clk,            // system clock
    input  wire        rst_n,          // active-low reset

    // Inputs
    input  wire [7:0]  buttons,        // 8 push buttons (active-high)
    input  wire [7:0]  dips,           // 8 DIP switches (active-high)
    input  wire        toggle_btn,     // 1 toggle button (mode / gate)
    input  wire        RX0,            // general purpose input (serial or anything)
    input  wire        RX1,            // general purpose input (serial or anything)
    input  wire [31:0] in_bus0,        // 32-bit input bus #0
    input  wire [31:0] in_bus1,        // 32-bit input bus #1

    // Outputs
    output wire [7:0] sevenseg0,     // right digit
    output wire [7:0] sevenseg1,     // left digit
    output reg  [31:0] out_bus0,       // 32-bit output bus #0
    output reg  [31:0] out_bus1,       // 32-bit output bus #1
    output wire        pwm_r,          // PWM R (or buzzer)
    output wire        pwm_g,          // PWM G
    output wire        pwm_b,          // PWM B
    output wire        pwm_gen,        // General-purpose PWM
    output reg  [7:0]  leds,           // 8 discrete LEDs
    output reg         TX0,            // general purpose output (loopback)
    output reg         TX1             // general purpose output (loopback)
);

    // =========================================================================
    // Reset synchronizer (convert rst_n to a clean synchronous reset 'rst')
    // =========================================================================
    reg [1:0] rst_sync;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            rst_sync <= 2'b00;
        else
            rst_sync <= {rst_sync[0], 1'b1};
    end
    wire rst = ~rst_sync[1]; // active-high internal reset

    // =========================================================================
    // Simple registered loopback for RX0/RX1 -> TX0/TX1
    // =========================================================================
    always @(posedge clk) begin
        if (rst) begin
            TX0 <= 1'b0;
            TX1 <= 1'b0;
        end else begin
            TX0 <= RX0;
            TX1 <= RX1;
        end
    end

    // =========================================================================
    // LEDs: demo logic -> XOR buttons and dips
    // =========================================================================
    always @(posedge clk) begin
        if (rst)
            leds <= 8'h00;
        else
            leds <= buttons ^ dips;
    end

    // =========================================================================
    // Seven-segment: show #buttons pressed (left) and dips[3:0] (right)
    // Each display = 8 bits: {dp, g, f, e, d, c, b, a} active-low common-anode
    // If yours is common-cathode, invert the outputs.
    // =========================================================================

    // Count number of pressed buttons (0..8), saturate to 0xF for safety
    function [3:0] popcount8;
        input [7:0] v;
        integer i;
        reg [3:0] c;
        begin
            c = 4'd0;
            for (i = 0; i < 8; i = i + 1)
                c = c + (v[i] ? 4'd1 : 4'd0);
            popcount8 = c;
        end
    endfunction

    wire [3:0] nibble_left  = popcount8(buttons); // 0..8
    wire [3:0] nibble_right = dips[3:0];

    function [7:0] sevenseg_hex; // active-low segments for hex 0..F + dp=1(off)
        input [3:0] hex;
        begin
            //          dp g f e d c b a  (active-low)
            case (hex)
                4'h0: sevenseg_hex = 8'b11000000; // 0
                4'h1: sevenseg_hex = 8'b11111001; // 1
                4'h2: sevenseg_hex = 8'b10100100; // 2
                4'h3: sevenseg_hex = 8'b10110000; // 3
                4'h4: sevenseg_hex = 8'b10011001; // 4
                4'h5: sevenseg_hex = 8'b10010010; // 5
                4'h6: sevenseg_hex = 8'b10000010; // 6
                4'h7: sevenseg_hex = 8'b11111000; // 7
                4'h8: sevenseg_hex = 8'b10000000; // 8
                4'h9: sevenseg_hex = 8'b10010000; // 9
                4'hA: sevenseg_hex = 8'b10001000; // A
                4'hB: sevenseg_hex = 8'b10000011; // b
                4'hC: sevenseg_hex = 8'b11000110; // C
                4'hD: sevenseg_hex = 8'b10100001; // d
                4'hE: sevenseg_hex = 8'b10000110; // E
                4'hF: sevenseg_hex = 8'b10001110; // F
                default: sevenseg_hex = 8'b11111111; // blank
            endcase
        end
    endfunction

    wire [7:0] seg_left  = sevenseg_hex(nibble_left);
    wire [7:0] seg_right = sevenseg_hex(nibble_right);

    assign sevenseg0 = seg_right; // right display (dips[3:0])
    assign sevenseg1 = seg_left;  // left display (#buttons pressed)

    // =========================================================================
    // Output buses: simple demo transforms
    // =========================================================================
    always @(posedge clk) begin
        if (rst) begin
            out_bus0 <= 32'd0;
            out_bus1 <= 32'd0;
        end else begin
            out_bus0 <= in_bus0 + in_bus1;                       // integer sum
            out_bus1 <= {in_bus0[15:0], in_bus1[15:0]};          // concat halves
            // Note: If you pass IEEE-754 single/double bit patterns, these ops
            // are "bitwise"/integer. Replace with an FP core if you need real FP.
        end
    end

    // =========================================================================
    // PWM: 8-bit duty from buses
    // =========================================================================
    wire [7:0] duty_r   = in_bus0[7:0];
    wire [7:0] duty_g   = in_bus0[15:8];
    wire [7:0] duty_b   = in_bus0[23:16];
    wire [7:0] duty_gen = in_bus1[7:0];

    // Simple 8-bit free-running counter for PWM
    reg [7:0] pwm_cnt;
    always @(posedge clk) begin
        if (rst)
            pwm_cnt <= 8'd0;
        else
            pwm_cnt <= pwm_cnt + 8'd1;
    end

    // RGB PWMs
    assign pwm_r = (pwm_cnt < duty_r)   ? 1'b1 : 1'b0;
    assign pwm_g = (pwm_cnt < duty_g)   ? 1'b1 : 1'b0;
    assign pwm_b = (pwm_cnt < duty_b)   ? 1'b1 : 1'b0;

    // Gate the general PWM with toggle_btn
    // (Debounce externally if your button is noisy)
    assign pwm_gen = toggle_btn ? (pwm_cnt < duty_gen) : 1'b0;

endmodule
