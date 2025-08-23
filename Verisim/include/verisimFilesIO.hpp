#ifndef VERISIM_FILES_IO_HPP
#define VERISIM_FILES_IO_HPP

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace verisim_files_ns {
    enum ACCES_TYPE {
        fileOutput,
        fileInput
    };

    /* This data type store time stamp/value pairs */
    struct Pair {
        uint64_t time_stamp_ns;
        uint8_t value;
    };

    class VeriSimFilesIO {
    public:
        VeriSimFilesIO(const std::string& fileName, ACCES_TYPE accessType);
        ~VeriSimFilesIO();

        // Append one pair to the file
        void fileWrite(Pair& pair);

        // Load all pairs from file into memory
        void fileLoad();

        // Return the extracted pairs
        const std::vector<Pair>& getPairs();

    private:
        std::string fileName;
        std::vector<Pair> pairs;
    };

}

#endif
