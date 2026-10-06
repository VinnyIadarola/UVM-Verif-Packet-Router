import PacketRouter_p::*;

`default_nettype none
module PacketRouterTX (
    // Control Inputs
    input  logic [NUM_OUT_PORTS-1:0]    dest_ready,        // Destination is ready to accept a packet

    // Data Inputs
    input  packet_s                     fifo_head [NUM_OUT_PORTS],
    input  logic                        fifo_empty[NUM_OUT_PORTS],

    // FIFO Control Outputs
    output logic                        fifo_pop  [NUM_OUT_PORTS],

    // Control Outputs
    output logic [NUM_OUT_PORTS-1:0]    out_packet_valid, // Router says packet is valid

    // Data Outputs
    output packet_s                     packets_out[NUM_OUT_PORTS]
);



assign packets_out = fifo_head;


always_comb begin 
    fifo_pop = '{default: '0};
    out_packet_valid = '0;

    for(int i = 0; i != NUM_OUT_PORTS; ++i) begin
        if(!fifo_empty[i])
            out_packet_valid[i] = 1;

        if(dest_ready[i]) 
            fifo_pop[i] = 1; 
    end
end



endmodule
`default_nettype wire
