#include "../header/Transaction.hpp"

/***********************************************************
***                     Class Control                    ***
***********************************************************/
void Transaction::reset() {
    num_instances = 0;
}

void Transaction::set_input_width(size_t input_width) {
    if(input_width_set)
        throw std::logic_error("Trying to redeclare input width without reset T.id: " + num_instances);
    input_width_set = true;

    Transaction::input_width = input_width;
}

void Transaction::set_output_width(size_t output_width) {
    if(output_width_set)
        throw std::logic_error("Trying to redeclare output width without reset T.id: " + num_instances);
    output_width_set = true;

    Transaction::output_width = output_width;
}

bool Transaction::operator==(const Transaction& other) const {
    return id == other.id;
}




/***********************************************************
***                      Constructors                    ***
***********************************************************/
Transaction::Transaction() :
    inputs(DataInputs(input_width, output_width))
{ id = num_instances++; }

Transaction::Transaction(const Transaction&) = default;

Transaction::Transaction(Transaction&& t) noexcept :
    id(std::move(t.id)),
    inputs(std::move(t.inputs))
{}




/***********************************************************
***                       Operators                      ***
***********************************************************/
Transaction& Transaction::operator=(const Transaction&) = default;

Transaction& Transaction::operator=(Transaction&& t) {
    if(!input_width_set || !output_width_set)
        throw std::logic_error("A transaction was instantiated without setting widths");

    id  = std::move(t.id);
    inputs = std::move(t.inputs);

    return *this;
}



/***********************************************************
***                  Packets Manipulation                ***
***********************************************************/
bool Transaction::load_packet(Packet&& p, bool is_packet_valid) {
    if(packets_loaded == inputs.packets.size())
        throw std::out_of_range("Tried to load too many packets. pid: " + std::to_string(p.id));

    inputs.packets[packets_loaded] = std::move(p);
    inputs.packet_valid[packets_loaded] = is_packet_valid;

    ++packets_loaded;

    return packets_loaded == inputs.packets.size();
}


bool Transaction::load_ready(bool ready) {
    if(readies_loaded == inputs.dest_ready.size())
        throw std::out_of_range("Tried to load too many ready bits. txn.id: " + std::to_string(id));
    
    inputs.dest_ready[readies_loaded] = ready;

    ++readies_loaded;

    return readies_loaded == inputs.dest_ready.size();
}


/***********************************************************
***                    Packets Control                   ***
***********************************************************/
std::vector<Packet>::const_iterator Transaction::cbegin() {
    return inputs.packets.cbegin();
}

std::vector<Packet>::const_iterator Transaction::cend() {
    return inputs.packets.cend();
}

std::size_t TransactionHash::operator()(const Transaction& t) const {
        return IdHash{}(t.id);
    }
