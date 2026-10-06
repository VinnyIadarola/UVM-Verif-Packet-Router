#pragma once

#include <map>
#include <random>
#include <string_view>
#include <utility>
#include <algorithm>
#include <stdexcept>

#include "configs.hpp"

class RandGen {
    using Range = std::pair<uint, uint>;

    public:
        /************************* Class Constructors ************************/
        explicit RandGen(const RandomConfig& config);

        /************************* Class Operators ***************************/
        uint operator()(const char* s);

    private:
        /************************* Private Properties ************************/
        std::map<std::string_view, Range> uint_ranges;
        std::uniform_int_distribution<uint> dist;
        std::mt19937 rng;

        /*************************** Private Helpers **************************/
        uint get_range(uint min, uint max);
};