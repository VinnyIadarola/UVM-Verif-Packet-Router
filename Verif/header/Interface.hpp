
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

#include "Packet.hpp"
#include "StaticVector.hpp"



struct DataInputs {
        StaticVector<Packet> packets;
        BitVector packet_valid;
        BitVector dest_ready;

        DataInputs() = delete;

        DataInputs(std::size_t input_width, std::size_t output_width) :
            packets(StaticVector<Packet>(input_width)),
            packet_valid(BitVector(input_width)),
            dest_ready(BitVector(output_width))
        {}
};


struct DataOuputs {
        bool router_ready;
        StaticVector<Packet> packets;
        BitVector packet_valid;
        BitVector packed_rejected;

        DataOuputs() = delete;

        DataOuputs(std::size_t input_width, std::size_t output_width) :     
            packets(StaticVector<Packet>(output_width)),
            packet_valid(BitVector(output_width)),
            packed_rejected(BitVector(input_width))
        {}
};
