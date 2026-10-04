#pragma once

#include <bit>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>
#include <random>
#include <cmath>
#include <unordered_map>
#include <variant>
#include "StaticVector.hpp"
#include <cstring>

using BitVector = StaticVector<bool>;

template <typename T>
class WriteOnce {
public:
    WriteOnce& operator=(T val) {
        if(value.has_value())
            throw std::logic_error("Already assigned an value");

        value = std::move(val);
        return *this;
    }

    operator const T&() const {
        return value.value();
    }


private:
    std::optional<T> value;
};

using Id = WriteOnce<int>;

#include "Packet.hpp"
#include "configs.hpp"
#include "RandGen.hpp"
