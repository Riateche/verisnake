module snake(
    input left,
    input right,
    input up,
    input down,
    input clk,
    input video_clk,
    input [7:0] video_x,
    input [7:0] video_y,
    input reset,
    output [23:0] video_output
);

reg left_pressed;
reg right_pressed;
reg up_pressed;
reg down_pressed;

reg [7:0] current_x;
reg [7:0] current_y;

reg [3:0] counter;

localparam X_MAX = 20;
localparam Y_MAX = 30;

typedef enum bit [1:0] { LOW, NEUTRAL, HIGH } Delta;

wire [7:0] next_x_plus_one = current_x + {6'b0, dx};
wire [7:0] next_y_plus_one = current_y + {6'b0, dy};

Delta dx;
Delta dy;

reg [4:0] field [Y_MAX-1:0] [X_MAX-1:0];

always @(posedge clk) begin
    if (reset) begin
        counter <= 0;
        current_x <= 10;
        current_y <= 15;
        left_pressed <= 0;
        right_pressed <= 0;
        up_pressed <= 0;
        down_pressed <= 0;
        dx <= LOW;
        dy <= NEUTRAL;
    end else begin
        if (left) left_pressed <= 1;
        if (right) right_pressed <= 1;
        if (up) up_pressed <= 1;
        if (down) down_pressed <= 1;

        counter <= counter + 1;

        if (left_pressed && (dx != HIGH)) begin
            dx <= LOW;
            dy <= NEUTRAL;
        end else if (right_pressed && (dx != LOW)) begin
            dx <= HIGH;
            dy <= NEUTRAL;
        end else if (up_pressed && (dy != HIGH)) begin
            dx <= NEUTRAL;
            dy <= LOW;
        end else if (down_pressed && (dy != LOW)) begin
            dx <= NEUTRAL;
            dy <= HIGH;
        end

        if (counter == 0) begin
            left_pressed <= 0;
            right_pressed <= 0;
            up_pressed <= 0;
            down_pressed <= 0;

            field[current_y[4:0]][current_x[4:0]][4:4] = 1;
            field[current_y[4:0]][current_x[4:0]][3:2] = dx;
            field[current_y[4:0]][current_x[4:0]][1:0] = dy;

            if (next_x_plus_one == 0)
                current_x <= 0;
            else if (next_x_plus_one == X_MAX + 1)
                current_x <= X_MAX - 1;
            else
                current_x <= next_x_plus_one - 1;

            if (next_y_plus_one == 0)
                current_y <= 0;
            else if (next_y_plus_one == Y_MAX + 1)
                current_y <= Y_MAX - 1;
            else
                current_y <= next_y_plus_one - 1;

        end
    end
end

always @(posedge video_clk) begin
    if (current_x == video_x && current_y == video_y)
        video_output = 24'h_a000a0;
    else if (field[video_y[4:0]][video_x[4:0]][4])
        video_output = 24'h_202020;
    else
        video_output = 24'h_ffffff;
end

endmodule
