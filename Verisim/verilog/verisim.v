module verisim (
    input wire clk, // This is considered a 5 MHz clock
    output reg led
);
    reg [21:0] counter = 0;  // 21-bit counter

    initial begin
        led = 0; // initialize LED
    end

    // Blink LED at 1 Hz
    always @(posedge clk) begin
        counter <= counter + 1;
        if (counter == 2_500_000) begin
            led <= ~led;
            counter <= 0;
        end
    end
endmodule