#ifndef VERISIM_FILES_IO_HPP
#define VERISIM_FILES_IO_HPP

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

namespace verisim_ns {
    /* This data type store time stamp/value pairs */
    struct Pair {
        uint64_t time_stamp_ns;
        uint8_t value;
    };

    class VeriSimFileIn {
    public:
        VeriSimFileIn(const std::string& fileName);
        ~VeriSimFileIn();
        const std::vector<Pair>& getPairs() const;
    private:
        // Load all pairs from file into memory
        void fileLoad();
    private:
        std::ifstream inputFile;
        std::string fileName;
        std::vector<Pair> pairs;
        bool is_file_open = false;
    };

}

#endif
