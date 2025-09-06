/*

// Use:
CData a = 0xAB;
SData b = 0x1234;
IData c = 0x40490FDB; // 3.1415927f

display::printDec(a, "a dec");
display::printHex(b, "b hex");
display::printBin(c, "c bin");
display::printFloat(c, "c float");
display::printChar(0x38, "c char");
display::printInt(c, "c int");

// Result:
a dec: 171
b hex: 0x1234
c bin: 01000000010010010000111111011011
c float: 3.14159
c char: '8'
c int: 1078530011

*/

#ifndef DATA_DISPLAY_HPP
#define DATA_DISPLAY_HPP

#include <iostream>
#include <iomanip>
#include <bitset>
#include "verilated.h"

namespace ns_jupiter {

    // ---------- Decimal ----------
    template<typename T>
    inline void printDec(const T& val, const char* label = "") {
        if(label && *label) std::cout << label << ": ";
        std::cout << +val << std::endl;
    }

    // ---------- Hex ----------
    template<typename T>
    inline void printHex(const T& val, const char* label = "") {
        if(label && *label) std::cout << label << ": ";
        std::cout << "0x" << std::hex << std::uppercase << +val << std::dec << std::endl;
    }

    // ---------- Binary ----------
    template<typename T>
    inline void printBin(const T& val, const char* label = "") {
        if(label && *label) std::cout << label << ": ";
        std::cout << std::bitset<sizeof(T)*8>(val) << std::endl;
    }

    // ---------- Interpret as float ----------
    inline void printFloat(const IData& val, const char* label = "") {
        if(label && *label) std::cout << label << ": ";
        std::cout << *reinterpret_cast<const float*>(&val) << std::endl;
    }

    // ---------- Interpret as char ----------
    inline void printChar(const IData& val, const char* label = "") {
        if(label && *label) std::cout << label << ": ";
        std::cout << "'" << (unsigned char)(val & 0xFF) << "'" << std::endl;
    }


    // ---------- Interpret as int ----------
    inline void printInt(const IData& val, const char* label = "") {
        if(label && *label) std::cout << label << ": ";
        std::cout << val << std::endl;
    }

    // Convenience overloads for CData and SData
    inline void printDec(const CData& val, const char* label = "") { printDec<uint8_t>(val, label); }
    inline void printHex(const CData& val, const char* label = "") { printHex<uint8_t>(val, label); }
    inline void printBin(const CData& val, const char* label = "") { printBin<uint8_t>(val, label); }

    inline void printDec(const SData& val, const char* label = "") { printDec<uint16_t>(val, label); }
    inline void printHex(const SData& val, const char* label = "") { printHex<uint16_t>(val, label); }
    inline void printBin(const SData& val, const char* label = "") { printBin<uint16_t>(val, label); }

    inline void printDec(const IData& val, const char* label = "") { printDec<uint32_t>(val, label); }
    inline void printHex(const IData& val, const char* label = "") { printHex<uint32_t>(val, label); }
    inline void printBin(const IData& val, const char* label = "") { printBin<uint32_t>(val, label); }

} // namespace ns_jupiter

#endif // DATA_DISPLAY_HPP
