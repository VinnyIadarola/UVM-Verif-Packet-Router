import PacketRouter_p::*;

`default_nettype none
interface PacketRouter_if(
    input bit clk
);
    // System Inputs
    logic                         rst_n;

    // Control Inputs
    logic [NUM_IN_PORTS-1:0]      in_packet_valid;
    logic [NUM_OUT_PORTS-1:0]     out_ready;


    // Data Inputs
    packet_s                      packets_in [NUM_IN_PORTS];

    // Control Outputs
    logic [NUM_OUT_PORTS-1:0]     out_packet_valid;
    logic                         router_ready;

    // Data Outputs
    packet_s                      packets_out [NUM_OUT_PORTS];
    logic                         packed_rejected [NUM_IN_PORTS];

    clocking cb @(posedge clk);
   

        // Control Inputs
        input  in_packet_valid;
        input  out_ready;
        input  timeout;

        // Data Inputs
        input  packets_in;

        // Control Outputs
        output out_packet_valid;
        output router_ready;

        // Data Outputs
        output packets_out;
        output packed_rejected;
    endclocking


    modport DUT (
    input input_ports,
    output output_ports
    );

endinterface
`default_nettype wire
