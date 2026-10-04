#include "../header/Transaction.hpp"
using namespace std;


/***********************************************************
***                     Class Control                    ***
***********************************************************/
void Transaction::reset() {
    num_instances = 0;
}

void Transaction::set_input_width(size_t input_width) {
    if(input_width_set)
        throw logic_error("Trying to redeclare input width without reset T.id: " + num_instances);
    input_width_set = true;

    Transaction::input_width = input_width;
}

void Transaction::set_output_width(size_t output_width) {
    if(output_width_set)
        throw logic_error("Trying to redeclare output width without reset T.id: " + num_instances);
    output_width_set = true;

    Transaction::output_width = output_width;

}


/***********************************************************
***                      Constructors                    ***
***********************************************************/
Transaction::Transaction() :
    bfm(BFM(input_width, output_width))
{ id = num_instances++; }


Transaction::Transaction(const Transaction&) = default;

Transaction::Transaction(Transaction&& t) noexcept :
    id(std::move(t.id)),
    bfm(std::move(t.bfm))
{}



/***********************************************************
***                       Operators                      ***
***********************************************************/
Transaction& Transaction::operator=(const Transaction&) = default;

Transaction& Transaction::operator=(Transaction&& t) {
    if(!input_width_set || !output_width_set)
        throw logic_error("A transaction was instantiated without setting widths");
        
    id  = std::move(t.id);
    bfm = std::move(t.bfm);

    return *this;
}


/***********************************************************
***                  Packets Manipulation                ***
***********************************************************/
bool Transaction::load_packet(Packet&& p, bool is_packet_valid) {
    if(num_loaded == bfm.packets.size())
        throw out_of_range("Tried to load too many packets. pid: " + std::to_string(p.id));

    bfm.packets[num_loaded] = std::move(p);
    bfm.validity_vector[num_loaded] = is_packet_valid;

    ++num_loaded;


    return num_loaded == bfm.packets.size();
}




/***********************************************************
***                    Packets Control                   ***
***********************************************************/
std::vector<Packet>::const_iterator Transaction::cbegin() {
    return bfm.packets.cbegin();
}

std::vector<Packet>::const_iterator Transaction::cend() {
    return bfm.packets.cend();
}
