#include "../header/Packet.hpp"

#include <stdexcept>
#include <utility>
using namespace std;


/**************************************************************
***                      System Controls                    ***
**************************************************************/
void Packet::set_addr_width(size_t addr_width) {
    if(addr_width_set)
        throw logic_error("Packet addr width was already set. number of packet instances: " + num_instants);

    addr_width = addr_width;
    addr_width_set = true;
}

void Packet::set_data_width(size_t data_width) {
    if(data_width_set)
        throw logic_error("Packet data width was already set. number of packet instances: " + num_instants);

    data_width = data_width;
    data_width_set = true;
}

void Packet::reset() {
    throw std::logic_error("Generator::reset is not implememted");
}


/**************************************************************
***                       Constructors                      ***
**************************************************************/
Packet::Packet(uint data_val, uint addr_val)
    : addr(BitVector(addr_width)),
      data(BitVector(data_width))
{
    if (!addr_width_set || !data_width_set) 
        throw logic_error("Packet widths were not set");

    load(addr, addr_val);
    load(data, data_val);

    id = num_instants++;
}


Packet::Packet(Packet&& p) noexcept
    : addr(move(p.addr)),
      data(move(p.data)),
      id(move(p.id))
{
    if (!addr_width_set || !data_width_set)
        throw logic_error("Packet widths were not set");
}


/**************************************************************
***                     Class Operators                     ***
**************************************************************/
bool Packet::operator==(const Packet &p) const
{
    return id == p.id;
}


/**************************************************************
***                     Class Operators                     ***
**************************************************************/
Packet& Packet::operator=(Packet&& p) noexcept {
    if (this != &p) {
        addr = move(p.addr);
        data = move(p.data);
        id = move(p.id);
    }

    return *this;
}


/**************************************************************
***                     Helper Functions                    ***
**************************************************************/
void load(BitVector &v, uint val) {
    for(uint i = 0; i != v.size(); ++i) {
        v[i] = val & (1 << i);
    }
};


struct PacketHash {
    std::size_t operator()(const Packet& p) const {
        return IdHash{}(p.id);
    }
};