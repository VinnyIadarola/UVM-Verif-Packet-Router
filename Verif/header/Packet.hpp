#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

#include "Id.hpp"
#include "StaticVector.hpp"

class Packet {
    public:
        /************************* Public Properties *************************/
        Id id;

        /************************* System Controls ***************************/
        static void set_data_width(size_t data_width);
        static void set_addr_width(size_t output_width);
        void reset();

        /************************* Class Constructors ************************/
        Packet(uint data, uint addr);
        Packet(Packet&& p) noexcept;
        Packet(const Packet&) = default;

        /************************* Class Operators ***************************/
        bool operator==(const Packet& p) const;
        Packet& operator=(Packet&& p) noexcept;
        Packet& operator=(const Packet&) = default;

    private:
        /************************* Private Properties ************************/
        BitVector addr;
        BitVector data;

        /********************** Static Private Properties *******************/
        inline static int num_instants = 0;

        inline static bool addr_width_set = false;
        inline static size_t addr_width;

        inline static bool data_width_set = false;
        inline static size_t data_width;
};

struct PacketHash {
    std::size_t operator()(const Packet& p) const;
};

