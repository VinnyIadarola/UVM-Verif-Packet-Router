`include "PacketRouter_p.sv"

import PacketRouter_p::*;

`default_nettype none
module PrioritySelectMux (
    // Control Inputs
    input logic [NUM_IN_PORTS-1:0]       curr_dest,
    
    // Data Inputs
    input packet_s                         data_in [NUM_IN_PORTS],

    // Control Outputs
    output logic [NUM_IN_PORTS-1:0]      next_dest,
    output logic                             valid,

    //Data Outputs
    output packet_s                       data_out
);


    /*************************************************************************************
    ***                              Leading One Detector                              ***
    *************************************************************************************/
    logic found;

    assign valid = |curr_dest;


    always_comb begin 
        found = 0;
        data_out = 'x;
        next_dest = curr_dest;


        if(valid) begin //I imagine this helps useless switching
            for(integer i = 0; i != NUM_IN_PORTS; ++i) begin
                if(!found && curr_dest[i]) begin
                    found = 1;
                    next_dest[i] = 0;
                    data_out = data_in[i];
                end
            end
        end
    end



endmodule
`default_nettype wire