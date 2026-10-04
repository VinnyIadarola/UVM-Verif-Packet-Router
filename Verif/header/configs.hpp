#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

#include "Packet.hpp"
#include "StaticVector.hpp"

constexpr unsigned clog2(std::uint64_t x) {
    return x <= 1 ? 0 : std::bit_width(x - 1);
}


struct DUT_Config {
    int DATA_WIDTH = 16;
    int NUM_IN_PORTS = 2;
    int NUM_OUT_PORTS = 4;
    int ADDR_WIDTH = clog2(NUM_OUT_PORTS);
    int TOTAL_WIDTH = DATA_WIDTH + ADDR_WIDTH;
    int FIFO_SIZE = 2 * NUM_IN_PORTS;
    int TIMEOUT_WIDTH = 2 * NUM_IN_PORTS;
};

//abstract to general test config and extended by Router_test_config

struct Test_Config {
    uint delay_min;
    uint delay_max;
    uint addr_min;
    uint addr_max;
    uint data_min;
    uint data_max;
    uint validity_prob;
    uint32_t seed;
};

struct BFM {
        StaticVector<Packet> packets;
        BitVector validity_vector;
        BitVector ready_vector;

        BFM() = delete;


        BFM(std::size_t input_width, std::size_t output_width) :
            packets(StaticVector<Packet>(input_width)),
            validity_vector(BitVector(input_width)),
            ready_vector(BitVector(output_width))
        {}


};