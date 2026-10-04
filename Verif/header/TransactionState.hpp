#pragma once

#include <stdexcept>
#include <unordered_map>

#include "Id.hpp"
#include "RouterRegression.hpp"

class Transaction;

class TransactionState {
    public:
        void grab_state(const Transaction& txn);

        void mark_packet_complete(Id id) {
            try {
                bool &seen = valid_ids.at(id);
                if(seen)
                    fail(DUPLICATE_PACKET);
                
                seen = true;


            } catch(const std::out_of_range& e) {
                fail(TestFail::PACKET_NOT_FOUND);
            }
            

        }

    private:
        std::unordered_map<Id, bool> valid_ids;
        bool transaction_completed;


};
