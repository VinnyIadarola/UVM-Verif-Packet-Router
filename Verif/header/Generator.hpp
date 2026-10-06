#pragma once

#include <stdexcept>
#include <utility>

#include "Packet.hpp"
#include "RandGen.hpp"
#include "StaticVector.hpp"
#include "configs.hpp"
#include "Transaction.hpp"

class Generator {
    public:
        /********************** System Control **********************/
        static void reset();

        /********************** Constructor **********************/
        Generator(const PacketRouterConfig &dut_config, const RandomConfig &testConfig);
        Generator() = delete;



        /********************** Generation Control **********************/
        Transaction next();

    private:
        /********************** Private Properties **********************/
        StaticVector<uint> valid_delays;
        StaticVector<uint> ready_delays;

        RandGen rand_gen;
    
        /********************** Generation Helpers **********************/
        template <typename DelayContainer, typename Loader>
        void create_with_delays(Transaction &txn, DelayContainer &delays, Loader loader);
};
