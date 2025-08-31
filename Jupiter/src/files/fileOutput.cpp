#include "fileOutput.hpp"
#include "fileInput.hpp" // for Pair definition

#include <stdexcept>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <cstring> 

namespace ns_jupiter {
    FileOut::FileOut(const std::string& fileName) {
        outputFile.open(fileName, std::ios::app); // append mode
        is_file_open = outputFile.is_open();

        if (!is_file_open) {
            throw std::runtime_error("[ERROR] Could not open output file for writing");
        }
    }

    FileOut::~FileOut() {
        if (is_file_open) {
            outputFile.close();
        }
    }

    static std::string formatValue(uint32_t value, OutputFormat fmt) {
        std::ostringstream oss;
        switch (fmt) {
            case OutputFormat::DECIMAL:
                oss << value;
                break;
            case OutputFormat::HEX:
                oss << "0x" << std::hex << std::uppercase << value;
                break;
            case OutputFormat::BINARY:
                oss << "0b" << std::bitset<32>(value);
                break;
            case OutputFormat::FLOAT: {
                float f;
                std::memcpy(&f, &value, sizeof(float)); // reinterpret bits as float
                oss << f;
                break;
            }
        }
        return oss.str();
    }

    void FileOut::append(uint64_t time_stamp_ns, uint32_t value, OutputFormat fmt) {
        if (!is_file_open) {
            throw std::runtime_error("[ERROR] Output file is not open");
        }
        outputFile << time_stamp_ns << " " << formatValue(value, fmt) << "\n";
    }

}
