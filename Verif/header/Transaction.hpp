#pragma once

#include <cstddef>
#include <vector>

#include "Id.hpp"
#include "Packet.hpp"
#include "TransactionState.hpp"
#include "configs.hpp"




class Transaction {
    public:
        Id id;

        /********************** Class Control **********************/
        static void reset();
        static void set_input_width(size_t input_width);
        static void set_output_width(size_t input_width);

        bool operator==(const Transaction &other) const;

        /********************** Constructor **********************/
        Transaction();

        Transaction(const Transaction&);
        Transaction(Transaction&& t) noexcept;

        /********************** Operators **********************/
        Transaction& operator=(const Transaction&);
        Transaction& operator=(Transaction&& t);


   
        /********************** Packets Manipulation **********************/

        bool load_packet(Packet&& p, bool is_packet_valid);

        /********************** Packets Control **********************/
        std::vector<Packet>::const_iterator cbegin();
        std::vector<Packet>::const_iterator cend();

        /*********************    *********************/
        friend class TransactionState;



        
    private:
        
        inline static bool input_width_set = false;
        inline static bool output_width_set = false;

        inline static size_t  input_width;
        inline static size_t output_width;

        inline static int num_instances = 0;
        int num_loaded = 0;
        BFM bfm;
 
};

struct TransactionHash {
    std::size_t operator()(const Transaction& t) const {
        return IdHash{}(t.id);
    }
};
