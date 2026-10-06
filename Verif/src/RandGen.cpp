#include "../header/RandGen.hpp"



/***********************************************************
***                   Class Constructor                  ***
***********************************************************/
RandGen::RandGen(const RandomConfig& config)
    : uint_ranges{
        { "valid", { config.valid_delay_min, config.valid_delay_max } },
        { "addr",  { config.addr_min,        config.addr_max        } },
        { "data",  { config.data_min,        config.data_max        } },
        { "ready", { config.ready_delay_min, config.ready_delay_max } }
    },

    rng(config.seed)
{}

/***********************************************************
***                   Class Operators                    ***
***********************************************************/
uint RandGen::operator()(const char* s) {
    std::string_view name{s};

    if (auto it = uint_ranges.find(name); it != uint_ranges.end()) {
        const auto& [min, max] = it->second;

        return get_range(min, max);
    }



    throw std::invalid_argument("Invalid distribution");
}

/***********************************************************
***                   Private Helpers                    ***
***********************************************************/
uint RandGen::get_range(uint min, uint max) {
    return dist(
        rng,
        std::uniform_int_distribution<uint>::param_type(min, max)
    );
}