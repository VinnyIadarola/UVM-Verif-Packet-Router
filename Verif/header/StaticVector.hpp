#pragma once

#include <cstddef>
#include <vector>


template <typename T>
class StaticVector {
    public:
        StaticVector() = delete;
        explicit StaticVector(std::size_t size) : v(size) {}

        typename std::vector<T>::reference operator[](std::size_t i) {
            return v[i];
        }

        typename std::vector<T>::const_reference operator[](std::size_t i) const {
            return v[i];
        }

        void clear() {
            v.clear();
        }

        std::size_t size() const {
            return v.size();
        }

         auto begin() {
            return v.begin();
        }

        auto end() {
            return v.end();
        }

        auto cbegin() const {
            return v.begin();   
        }

        auto cend() const {
            return v.end();     
        }

        
        
    private:
        std::vector<T> v;

  

};
