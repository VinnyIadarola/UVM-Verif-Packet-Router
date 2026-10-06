#pragma once

#include <cstddef>
#include <functional>
#include <optional>
#include <stdexcept>
#include <utility>

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

struct IdHash {
    std::size_t operator()(const Id& id) const {
        return std::hash<int>{}(id);
    }
};
