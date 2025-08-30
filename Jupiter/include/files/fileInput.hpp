#ifndef FILE_INPUT_HPP
#define FILE_INPUT_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

namespace ns_jupiter {
    /* This data type store time stamp/value pairs */
    struct Pair {
        uint64_t time_stamp_ns;
        uint32_t value;
    };

    class FileIn {
    public:
        FileIn(const std::string& fileName);
        ~FileIn();
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