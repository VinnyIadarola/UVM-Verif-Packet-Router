#pragma once

#include <cstddef>
#include <unordered_map>

#include "Packet.hpp"
#include "Transaction.hpp"
#include "TransactionState.hpp"
#include "configs.hpp"



class Scoreboard {
    public:
        Scoreboard() = delete;
        Scoreboard(const DUT_Config &dut_config, const Test_Config &testConfig) {

        }






    private:
        std::unordered_map<Packet*, Transaction*, PacketHash> packet_to_transaction;
        std::unordered_map<Transaction, size_t, TransactionHash> scoreboard;
        


};
