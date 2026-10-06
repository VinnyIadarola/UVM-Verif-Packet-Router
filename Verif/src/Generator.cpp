#include "../header/Generator.hpp"



/***********************************************************
***                     System Control                   ***
***********************************************************/
void Generator::reset() {
    throw std::logic_error("Generator::reset is not implememted");
}

/***********************************************************
***                      Constructors                    ***
***********************************************************/
Generator::Generator(const PacketRouterConfig &dut_config, const RandomConfig &test_config) :
    valid_delays(StaticVector<uint>(dut_config.NUM_IN_PORTS)),
    ready_delays(StaticVector<uint>(dut_config.NUM_OUT_PORTS)),
    rand_gen(RandGen(test_config))
{

    for(auto &count : valid_delays)
        count = rand_gen("valid");

    for(auto &count : ready_delays)
        count = rand_gen("ready");

   

    Transaction::set_input_width(dut_config.NUM_IN_PORTS);
    Transaction::set_output_width(dut_config.NUM_OUT_PORTS);

    Packet::set_data_width(dut_config.DATA_WIDTH);
    Packet::set_addr_width(dut_config.ADDR_WIDTH);
}



/***********************************************************
***                   Generation Control                 ***
***********************************************************/
Transaction Generator::next() {
    Transaction txn;
    //create Packets
    create_with_delays(
        txn,
        valid_delays,
        [&](bool valid) {
            return txn.load_packet(
                Packet(rand_gen("addr"),rand_gen("data")),
                valid
            );
        }
    );

    //Create Ready Vector
    create_with_delays(
        txn,
        ready_delays,
        [&](bool ready) {
            return txn.load_ready(ready);
        }
    );

    return txn;
}





/***********************************************************
***                   Generation helpers                 ***
***********************************************************/
template <typename DelayContainer, typename Loader>
void Generator::create_with_delays(
    Transaction& txn,
    DelayContainer& delays,
    Loader loader
) {
    auto delay_iter = delays.begin();
    bool txn_full = false;

    do {
        if (delay_iter == delays.end()) {
            throw std::logic_error(
                "Delay count accessed out of range during Transaction gen. txn.id: "
                + txn.id
            );
        }

        const bool active = (*delay_iter == 0);

        if (active) {
            *delay_iter = rand_gen("delay");
        } else {
            --(*delay_iter);
        }

        ++delay_iter;

        txn_full = loader(active);

    } while (!txn_full);
}



