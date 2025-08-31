#include "fileOutput.hpp"
#include "fileInput.hpp" // for Pair definition (optional, if you want symmetry)

#include <stdexcept>
#include <iomanip>

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

    void FileOut::append(uint64_t time_stamp_ns, uint32_t value) {
        if (!is_file_open) {
            throw std::runtime_error("[ERROR] Output file is not open");
        }
        outputFile << time_stamp_ns << " " << value << "\n";
    }

}
