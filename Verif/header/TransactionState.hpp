#pragma once

#include <stdexcept>
#include <unordered_map>

#include "Id.hpp"

class Transaction;

class TransactionState {
    public:
        void grab_state(const Transaction& txn);

        void mark_packet_complete(Id id);

    private:
        std::unordered_map<Id, bool> valid_ids;
        bool transaction_completed;

};
