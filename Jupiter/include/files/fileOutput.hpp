#ifndef FILE_OUTPUT_HPP
#define FILE_OUTPUT_HPP

#include <cstdint>
#include <string>
#include <fstream>

namespace ns_jupiter {
    struct Pair; // forward declaration for symmetry

    class FileOut {
    public:
        explicit FileOut(const std::string& fileName);
        ~FileOut();

        // Append a new time/value pair to the file
        void append(uint64_t time_stamp_ns, uint32_t value);

    private:
        std::ofstream outputFile;
        std::string fileName;
        bool is_file_open = false;
    };
}

#endif
