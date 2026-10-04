#pragma once

#include "imports.hpp"
#include "Transaction.hpp"





class Generator {
    public:
        /********************** Constructor **********************/
        Generator(const DUT_Config &dut_config, const Test_Config &testConfig);
        Generator() = delete;

        /********************** System Control **********************/
        void reset();

        /********************** Generation Control **********************/
        Transaction&& next();
        void load_transactions(Transaction &t);


    private:
        void init_dut_variables(const DUT_Config &dut_config);
        void init_test_variables(const Test_Config &test_config);

        StaticVector<uint> delay_counts;
        RandGen rand_gen;
        uint addr_width, data_width;
        







};
