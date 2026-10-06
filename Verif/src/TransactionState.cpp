#include "../header/TransactionState.hpp"

#include "../header/Transaction.hpp"

void TransactionState::grab_state(const Transaction& txn) {
    for (std::size_t i = 0; i != txn.input_width; ++i)
        if (txn.inputs.in_packet_valid[i])
            valid_ids[txn.inputs.packets[i].id] = false;
}

void TransactionState::mark_packet_complete(Id id) {
            try {
                bool &seen = valid_ids.at(id);
                if(seen)
                    fail(DUPLICATE_PACKET);

                seen = true;

            } catch(const std::out_of_range& e) {
                fail(TestFail::PACKET_NOT_FOUND);
            }

        }
