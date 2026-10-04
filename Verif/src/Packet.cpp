#include "../header/Packet.hpp"
using namespace std;

void Packet::set_addr_width(size_t addr_width) {
    addr_width = addr_width;
    addr_width_set = true;
}

void Packet::set_data_width(size_t data_width) {
    data_width = data_width;
    data_width_set = true;
}

Packet::Packet(uint data_val, uint addr_val)
    : addr(BitVector(addr_width)),
      data(BitVector(data_width))
{
    if (!addr_width_set || !data_width_set) {
        throw logic_error("Packet widths were not set");
    }

    load(addr, addr_val);
    load(data, data_val);


    id = num_instants++;
}

bool Packet::operator==(const Packet &p) const
{
    return id == p.id;
}

inline void load(BitVector &v, uint val) {

    for(uint i = 0; i != v.size(); ++i) {
        v[i] = val & (1 << i);
    }

}

Packet::Packet(Packet&& p) noexcept
    : addr(move(p.addr)),
      data(move(p.data)),
      id(move(p.id))
{
}

Packet& Packet::operator=(Packet&& p) noexcept {
    if (this != &p) {
        addr = move(p.addr);
        data = move(p.data);
        id = move(p.id);
    }

    return *this;
}