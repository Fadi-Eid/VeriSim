/* A set of functions to help manipulate IOs */

#ifndef VERISIM_HELPER_HPP
#define VERISIM_HELPER_HPP

#include "verilated.h"
#include <stdexcept>

/* Header only library */

namespace helper {
    /* Extract and return one bit at the desired index (idx 0 = LSB) */
    template<typename T>
    inline CData getBit(T data, uint8_t idx) {
        if (idx >= sizeof(T)*8) {
            throw std::out_of_range("Bit index is out of range");
        }
        return (data >> idx) & T(0x01);
    }

    /* Set one bit at the desired index (idx 0 = LSB) */
    template<typename T>
    inline void setBit(T& data, uint8_t idx) {
        if(idx >= sizeof(T)*8) {
            throw std::out_of_range("Bit index is out of range");
        }
        data = (T(0x01) << idx) | data;
    }

    /* Reset one bit at the desired index (idx 0 = LSB)*/
    template<typename T>
    inline void resetBit(T& data, uint8_t idx) {
        if(idx >= sizeof(T)*8) {
            throw std::out_of_range("Bit index is out of range");
        }
        data &= ~(T(0x01) << idx);
    }

    /* Flip a bit at the desired index (idx 0 = LSB) */
    template<typename T>
    inline void flipBit(T& data, uint8_t idx) {
        if(idx >= sizeof(T)*8) {
            throw std::out_of_range("Bit index is out of range");
        }
        data ^= (T(0x01) << idx);
    }
}

#endif