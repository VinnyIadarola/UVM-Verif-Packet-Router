`include "PacketRouter_p.sv"
import PacketRouter_p::*;
`include "PrioritySelectMux.sv"

`default_nettype none
module PacketRouterRX (
    //System Inputs
    input logic clk,
    input logic rst_n,

    //Control Inputs
    input logic   [NUM_IN_PORTS-1:0] in_packet_valid, // Sender states packet is valid
    input logic                            fifo_full [NUM_OUT_PORTS],

    //Data Inputs
    input packet_s                         packets_in [NUM_IN_PORTS],


    //Control Outputs
    output logic                        router_ready, // Router is ready to accept from Sender 
    output logic       [NUM_OUT_PORTS-1:0]  fifo_push, // Router is ready to accept from Sender 

    //Data Outputs
    output packet_s        fifo_write_data [NUM_OUT_PORTS]

);



    /*************************************************************************************
    ***                               State Machine Logic                              ***
    *************************************************************************************/
    typedef enum logic {IDLE, STORE} router_state_e;
    router_state_e curr_state, next_state;

    logic load_packet_state;
    logic store;
    logic all_packets_sorted;


    /*******************************      FSM Register     *******************************/
    always_ff @(posedge clk, negedge rst_n) begin
        if(~rst_n)
            curr_state <= IDLE;
        else 
            curr_state <= next_state;
    end

    /******************************    FSM Combinational    *******************************/
    always_comb begin
        next_state = curr_state;
        router_ready = 0;
        load_packet_state = 1'b0;
        store = 1'b0;



        unique case (curr_state)
            IDLE: begin
                router_ready = 1'b1;

                if (|in_packet_valid) begin
                    load_packet_state = 1'b1;
                    router_ready = 1'b0;
                    next_state = STORE;

                end
            end
            STORE: begin
                store = 1'b1;


                if(~|fifo_push) begin
                    next_state = IDLE;
                    store = 1'b1;
                end

            end
        endcase
    end



    /*************************************************************************************
    ***                                Router Data Register                            ***
    *************************************************************************************/
    /** 
    TODO: There is a stall issue as we cant load more packets until all other packets are cleared
        the solution is use my RingBuffer to after the PrioritySelectMux to store packets. 
        This will introduce a 1 clk delay but will allow more packets to load in. Also would need 2 fsm         
    **/
    packet_s data_storage [NUM_IN_PORTS];


    always_ff @(posedge clk) begin 
        if(load_packet_state) 
            data_storage <= packets_in;
    end



    /*************************************************************************************
    ***                              Destination Register                              ***
    *************************************************************************************/
    logic [NUM_IN_PORTS-1:0]  cached_dest [NUM_OUT_PORTS];
    logic [NUM_IN_PORTS-1:0]    next_dest [NUM_OUT_PORTS];


    always_ff @(posedge clk, negedge rst_n) begin
        if(~rst_n) 
            for (integer i = 0; i != NUM_OUT_PORTS; ++i) 
                cached_dest[i] <= '0;

        else if (load_packet_state) 
            for (integer i = 0; i != NUM_OUT_PORTS; ++i) 
                for (integer j = 0; j != NUM_IN_PORTS; ++j) 
                    cached_dest[i][j] <= (packets_in[j].addr == i) & in_packet_valid[j];
                    
        else if(store)
                for (integer i = 0; i != NUM_OUT_PORTS; ++i) 
                    if(~fifo_full[i])
                        cached_dest[i] <= next_dest[i];
    end



    
    /*************************************************************************************
    ***                                   Output Mux                                   ***
    *************************************************************************************/
    PrioritySelectMux channel_select [NUM_OUT_PORTS-1:0] (
        .curr_dest(cached_dest),
        .data_in(data_storage),
    
        //Data Outputs
        .data_out(fifo_write_data),
        .next_dest(next_dest),
        .valid(fifo_push)    
    );

    assign all_packets_sorted = ~|fifo_push;





endmodule
`default_nettype wire