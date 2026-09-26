import PacketRouter_p::*;


`default_nettype none
module PacketRouter (
    // System Inputs
    input  logic                         clk,
    input  logic                         rst_n,

    // Control Inputs
    input  logic [NUM_IN_PORTS-1:0]      in_packet_valid,   // Sender states packet is valid
    input  logic [NUM_OUT_PORTS-1:0]     out_ready,         // Destination is ready to accept a packet
    input  logic [TIMEOUT_WIDTH-1:0]     timeout,

    // Data Inputs
    input  packet_s                      packets_in [NUM_IN_PORTS],

    // Control Outputs
    output logic [NUM_OUT_PORTS-1:0]     out_packet_valid,  // Router says packet is valid
    output logic                         router_ready,      // Router is ready to accept from sender

    // Data Outputs
    output packet_s                      packets_out [NUM_OUT_PORTS],
    output logic                         packed_rejected [NUM_IN_PORTS]
);

    logic   [TOTAL_WIDTH-1:0] fifo_write_data [NUM_OUT_PORTS];
    logic                           fifo_full [NUM_OUT_PORTS];
    logic                          fifo_empty [NUM_OUT_PORTS];
    logic         [TOTAL_WIDTH-1:0] fifo_head [NUM_OUT_PORTS];
    logic       [NUM_OUT_PORTS-1:0] fifo_push;
    logic                            fifo_pop [NUM_OUT_PORTS];


    /*************************************************************************************
    ***                              Packet Router RX Instant                          ***
    *************************************************************************************/
    PacketRouterRX rx (
        //System Inputs
        .clk             (clk),
        .rst_n           (rst_n),

        //Control Inputs
        .in_packet_valid (in_packet_valid), 
        .fifo_full       (fifo_full),
        .timeout         (timeout),

        //Data Inputs
        .packets_in       (packets_in),

        //Control Outputs
        .router_ready    (router_ready), 
        .fifo_push       (fifo_push),   
        .packed_rejected (packed_rejected),

        //Data Outputs
        .fifo_write_data (fifo_write_data)
    );



  
    /*************************************************************************************
    ***                                Ring Buffer Instant                             ***
    *************************************************************************************/
    RingBuffer #(
        .DATA_WIDTH (TOTAL_WIDTH)
    ) fifo [NUM_OUT_PORTS-1:0] (
        // Basic Inputs
        .clk   (clk),
        .rst_n (rst_n),

        // Data Inputs
        .entry (fifo_write_data),

        // Control Inputs
        .push  (fifo_push), 
        .pop   (fifo_pop),

        //Data Outputs
        .head  (fifo_head),

        // Control Outputs
        .full  (fifo_full),
        .empty (fifo_empty)
    );

   

    /*************************************************************************************
    ***                               Packet Router TX Instant                         ***
    *************************************************************************************/
    PacketRouterTX tx (
        //Control Inputs
        .out_ready       (out_ready),

        //Data Inputs
        .fifo_head        (fifo_head),
        .fifo_empty       (fifo_empty),

        .fifo_pop         (fifo_pop),

        //Control Outputs
        .out_packet_valid (out_packet_valid), 

        //Data Outputs
        .packets_out      (packets_out)
    );



endmodule
`default_nettype wire