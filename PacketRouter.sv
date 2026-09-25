`include "PacketRouter_p.sv"
import PacketRouter_p::*;
`include "PrioritySelectMux.sv"

`default_nettype none
module PacketRouter (
    //System Inputs
    input logic clk,
    input logic rst_n,

    //Control Inputs
    input logic   [NUM_IN_PORTS-1:0] in_packet_valid, // Sender states packet is valid
    input logic  [NUM_OUT_PORTS-1:0]      dest_ready, // Destination is ready to accept a packet

    //Data Inputs
    input packet_s                          packet_in [NUM_IN_PORTS],


    //Control Outputs
    output logic [NUM_OUT_PORTS-1:0] out_packet_valid, // Router says packet is valid
    output logic                         router_ready, // Router is ready to accept from Sender 

    //Data Outputs
    output packet_s                        packets_out [NUM_OUT_PORTS]
);

    logic load_packet_state;




    /*************************************************************************************
    ***                                Router Data Storage                             ***
    *************************************************************************************/
    packet_s data_storage [NUM_IN_PORTS];

    always_ff @(posedge clk) begin 
        if(load_packet_state) 
            data_storage <= packet_in;
    end




    /*************************************************************************************
    ***                              Router Addr Storage                               ***
    *************************************************************************************/
    logic [NUM_IN_PORTS-1:0] dest_storage [NUM_OUT_PORTS];
    logic [NUM_IN_PORTS-1:0] next_destinations [NUM_OUT_PORTS];



    always_ff @(posedge clk) begin
        if (load_packet_state) 
            for (integer i = 0; i < NUM_OUT_PORTS; ++i) 
                for (integer j = 0; j < NUM_IN_PORTS; ++j) 
                    dest_storage[i][j] <= (packet_in[j].addr == i) & in_packet_valid[j];
        else 
            for (integer i = 0; i < NUM_OUT_PORTS; ++i) 
                if(dest_ready[i])
                    dest_storage[i] <= next_destinations[i] ;
            
    end




    /*************************************************************************************
    ***                              Router Addr Storage                               ***
    *************************************************************************************/
    PrioritySelectMux channel_select [NUM_OUT_PORTS-1:0] (
        .destinations(dest_storage),
        .data_in(data_storage),
    
        //Data Outputs
        .data_out(packets_out),
        .next_destinations(next_destinations),
        .valid(out_packet_valid)    
    );




    /*************************************************************************************
    ***                                   State Machine                                ***
    *************************************************************************************/
    typedef enum logic {IDLE, TRANSMIT} router_state_e;
    router_state_e curr_state, next_state;


    always_ff @(posedge clk, negedge rst_n) begin : FSM_FF
        if(~rst_n)
            curr_state <= IDLE;
        else 
            curr_state <= next_state;
    end


    always_comb begin : FSM_COMBINATIONAL
        //Default vals
        next_state = curr_state;
        router_ready = 0;

        case (curr_state)
            IDLE: begin
                router_ready = 1'b1;

                if (|in_packet_valid) begin
                    load_packet_state = 1'b1;
                    router_ready = 1'b0;
                    next_state = TRANSMIT;

                end
            end
            TRANSMIT: 

        endcase


    end






    
endmodule
`default_nettype wire