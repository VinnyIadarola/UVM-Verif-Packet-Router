
`ifndef PACKETROUTER_P
`define PACKETROUTER_P

`default_nettype none
package PacketRouter_p;
parameter int DATA_WIDTH = 16;
parameter int NUM_IN_PORTS = 2;
parameter int NUM_OUT_PORTS = 4;
parameter int ADDR_WIDTH = $clog2(NUM_OUT_PORTS);
parameter int TOTAL_WIDTH = DATA_WIDTH + ADDR_WIDTH;
parameter int FIFO_SIZE = 2 * NUM_IN_PORTS;
parameter int TIMEOUT_WIDTH = 2 * NUM_IN_PORTS;
        
typedef struct packed {
    logic [ADDR_WIDTH-1:0] addr;
    logic [DATA_WIDTH-1:0] data;
} packet_s;


endpackage
`default_nettype wire



`endif