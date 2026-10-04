#include "../header/Generator.hpp"

using namespace std;



/**************************************               Public               **************************************/
/***********************************************************
***                      Constructors                    ***
***********************************************************/
Generator::Generator(const DUT_Config &dut_config, const Test_Config &test_config) {
    init_dut_variables(dut_config);
    init_test_variables(test_config);




}

 

/***********************************************************
***                     System Control                   ***
***********************************************************/
void Generator::reset() {
    throw logic_error("Generator::reset is not implememted");
}



/***********************************************************
***                   Generation Control                 ***
***********************************************************/
Transaction Generator::next() {
    Transaction t;
    auto delay_iter = delay_counts.begin();
    bool load_success;
    do {
        if(delay_iter == delay_counts.end())
            throw logic_error("Delayed count was accessed out of range during Transaction gen.. T.id: " + t.id);

        bool valid = (*delay_iter) == 0;
        Packet p = Packet(rand_gen("addr"),  rand_gen("data"));

        *delay_iter = (valid) ? rand_gen("delay") : --*delay_iter; 
        ++delay_iter;

        load_success = t.load_packet(std::move(p), valid);
    } while(load_success);


     
    

    return t;
}




/**************************************               Private               **************************************/
void Generator::init_dut_variables(const DUT_Config &dut_config) {
    Transaction::set_input_width(dut_config.NUM_IN_PORTS);
    Transaction::set_output_width(dut_config.NUM_OUT_PORTS);

    Packet::set_data_width(dut_config.DATA_WIDTH);
    Packet::set_addr_width(dut_config.ADDR_WIDTH);



}

void Generator::init_test_variables(const Test_Config &test_config) {
    rand_gen = RandGen(test_config);

    for(auto &count : delay_counts)
        count = rand_gen("delay");

}
