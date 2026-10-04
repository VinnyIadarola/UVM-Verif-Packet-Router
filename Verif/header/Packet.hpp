#pragma once

#include "imports.hpp"

class Packet {
    public:
        BitVector addr;
        BitVector data;


        Id id;

        static void set_data_width(size_t data_width);
        static void set_addr_width(size_t output_width);

        Packet::Packet(uint data, uint addr);

        bool operator==(const Packet& p) const;

        Packet(const Packet&) = default;
        Packet& operator=(const Packet&) = default;

        Packet(Packet&& p) noexcept;
        Packet& operator=(Packet&& p) noexcept;

    private:
        inline static int num_instants = 0;

        inline static bool addr_width_set = false;
        inline static bool data_width_set = false;

        inline static size_t addr_width = 0;
        inline static size_t data_width = 0;
};


struct PacketHash {
    std::size_t operator()(const Packet& p) const {
        return IdHash{}(p.id);
    }
};


struct PacketPtrHash {
    std::size_t operator()(const Packet* p) const {
        return IdHash{}(p->id);
    }
};


struct PersonPtrEqual {
    bool operator()(const Packet* a, const Packet* b) const {
        return a->id == b->id;
    }
};
