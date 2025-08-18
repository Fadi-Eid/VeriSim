module verisim (
    input wire clk,
    output reg led
);
    reg [3:0] counter = 0;  // 4-bit counter

    initial begin
        led = 0; // initialize LED
    end

    always @(posedge clk) begin
        counter <= counter + 1;
        if (counter == 4'd3) begin  // toggle LED every 4 cycles
            led <= ~led;
            counter <= 0;
        end
    end
endmodule
