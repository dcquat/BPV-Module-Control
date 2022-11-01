`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/17/2022 07:47:43 PM
// Design Name: 
// Module Name: manual_control
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module manual_control(
    input enable,
    input clk,
    input [4:0] angle,
    input refl,
    input angle_set,
    input refl_set,
    input enter,
    input res,
    output reg [4:0] angle_out,
    output reg refl_out
    );
    
    //setting up registers
    //desired angle and reflector set are stored in register then 
    //ouput to control @ state three w/enter input set high
    reg [1:0] state;
    reg [1:0] next_state;

    
    parameter zero = 2'b00, one = 2'b01;
    parameter two = 2'b10, three = 2'b11;
    
    /*
    Assigning state logic
    Machine state logic is relatively simple. Complexity arises from the need
    to store inputs then output to control synchronously
    */
    always@(posedge clk)begin
    case(state)
        zero: begin
            
            if (enable == 1'b1)
                next_state = one;
            else
                next_state = zero;
            
        end
            
        one: begin
            
            if (angle_set == 1'b1)
                next_state = two;
            else
                next_state = one;
            end
            
        two: begin
            if (refl_set == 1'b1)
                next_state = three;
            else
                next_state = two;
            end
        
        three: begin
            if (enter == 1'b1)
                next_state = zero;
            else
                next_state = three;
            end
            
            
    endcase
    end
    
    always@(posedge clk) begin
        if(res)begin
            state = zero;
            angle_out = 4'b0000;
            refl_out = 1'b0;
        end
        
        else
            case(next_state)
                zero: begin
                    angle_out <= 4'b0000;
                    refl_out <= 1'b0;
                end
                
                one: begin
                    angle_out <= 4'b0000;
                    refl_out <= 1'b0;
                end
                
                two: begin 
                    angle_out <= angle;
                    refl_out <= 1'b0;
                end
                
                three: begin
                    angle_out <= angle;
                    refl_out <= refl;
                end
            
            endcase
        end
endmodule
