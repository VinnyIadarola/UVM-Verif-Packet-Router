    // Project dependencies
    #include "configs.hpp"
    #include "Packet.hpp"
    #include "Transaction.hpp"


#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

#include "Packet.hpp"
#include "StaticVector.hpp"

constexpr unsigned clog2(std::uint64_t x) {
    return x <= 1 ? 0 : std::bit_width(x - 1);
}

struct PacketRouterConfig {
    int DATA_WIDTH = 16;
    int NUM_IN_PORTS = 2;
    int NUM_OUT_PORTS = 4;
    int ADDR_WIDTH = clog2(NUM_OUT_PORTS);
    int TOTAL_WIDTH = DATA_WIDTH + ADDR_WIDTH;
    int FIFO_SIZE = 2 * NUM_IN_PORTS;
    int TIMEOUT_WIDTH = 2 * NUM_IN_PORTS;
};

//abstract to general test config and extended by Router_test_config

struct RandomConfig {
    uint delay_min;
    uint delay_max;
    uint addr_min;
    uint addr_max;
    uint data_min;
    uint data_max;
    uint validity_prob;
    uint32_t seed;
};


  


    int main() {


    }