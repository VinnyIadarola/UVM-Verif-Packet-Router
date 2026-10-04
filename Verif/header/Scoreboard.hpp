#include "imports.hpp"
#include <unordered_map>



class Scoreboard {
    public:
        Scoreboard() = delete;
        Scoreboard(const DUT_Config &dut_config, const Test_Config &testConfig) {

        }






    private:
        std::unordered_map<Packet*, Transaction*, PacketHash> packet_to_transaction;
        std::unordered_map<Transaction, size_t, TransactionHash> scoreboard;
        


};


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


}





