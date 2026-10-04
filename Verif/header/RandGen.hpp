#pragma once

#include <algorithm>
#include <cstring>
#include <random>
#include <stdexcept>

#include "configs.hpp"




class RandGen  {
public:
    explicit RandGen(const Test_Config& config) : 
        config(&config),
        rng(config.seed)
    {}

    uint operator()(const char* s) {
        if (std::strcmp(s, "delay") == 0)
            return get_range(config->delay_min, config->delay_max);

        if (std::strcmp(s, "addr") == 0)
            return get_range(config->addr_min, config->addr_max);

        if (std::strcmp(s, "data") == 0)
            return get_range(config->data_min, config->data_max);

        if (std::strcmp(s, "validity") == 0)
            return get_range(1, 100) <= std::min(config->validity_prob, 100u);

        if (std::strcmp(s, "ready") == 0)
            return get_range(1, 100) <= std::min(config->validity_prob, 100u);



        throw std::invalid_argument("Invalid distribution");
    }

private:
    std::uniform_int_distribution<uint> dist;
    const Test_Config* config;
    std::mt19937 rng;

    uint get_range(uint min, uint max) {
        return dist(rng, std::uniform_int_distribution<uint>::param_type(min, max));
    }

 
};