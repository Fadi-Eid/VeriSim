#ifndef VERISIM_HELPER_HPP
#define VERISIM_HELPER_HPP

#include "verilated.h"
#include <stdexcept>
#include <limits>
#include <type_traits>

namespace verisim_ns {

    template<typename T>
    inline bool getBit(T data, uint8_t idx) {
        static_assert(std::is_integral<T>::value, "T must be integral");
        if (idx >= sizeof(T) * 8) {
            throw std::out_of_range("Bit index is out of range");
        }
        return (data >> idx) & T(0x01);
    }

    template<typename T>
    inline void setBit(T& data, uint8_t idx) {
        static_assert(std::is_integral<T>::value, "T must be integral");
        if (idx >= sizeof(T) * 8) {
            throw std::out_of_range("Bit index is out of range");
        }
        data |= (T(0x01) << idx);
    }

    template<typename T>
    inline void resetBit(T& data, uint8_t idx) {
        static_assert(std::is_integral<T>::value, "T must be integral");
        if (idx >= sizeof(T) * 8) {
            throw std::out_of_range("Bit index is out of range");
        }
        data &= ~(T(0x01) << idx);
    }

    template<typename T>
    inline void flipBit(T& data, uint8_t idx) {
        static_assert(std::is_integral<T>::value, "T must be integral");
        if (idx >= sizeof(T) * 8) {
            throw std::out_of_range("Bit index is out of range");
        }
        data ^= (T(0x01) << idx);
    }

    template<typename T>
    inline void setData(T& data) {
        static_assert(std::is_integral<T>::value, "T must be integral");
        data = std::numeric_limits<T>::max();
    }

    template<typename T>
    inline void resetData(T& data) {
        static_assert(std::is_integral<T>::value, "T must be integral");
        data = T(0x00);
    }

    template<typename T>
    inline void flipData(T& data) {
        static_assert(std::is_integral<T>::value, "T must be integral");
        data ^= static_cast<T>(std::numeric_limits<T>::max());
    }
}

#endif
