#include "verisimFilesIO.hpp"
#include <iostream>

namespace verisim_ns {

    VeriSimFileIn::VeriSimFileIn(const std::string& fileName) {
        inputFile.open(fileName);
        is_file_open = inputFile.is_open();
        fileLoad();
    }

    VeriSimFileIn::~VeriSimFileIn() {
        if (is_file_open) {
            inputFile.close();
        }
    }
    const std::vector<Pair>& VeriSimFileIn::getPairs() const {
        return pairs;
    }

    void VeriSimFileIn::fileLoad() {
        if (!is_file_open) {
            throw std::runtime_error("[ERROR] Could not open input file");
        }

        std::string line;
        Pair previousPair{0, 0};

        while (std::getline(inputFile, line)) {
            // Skip empty lines
            if (line.empty()) continue;
            
            // Skip comment lines
            if (line[0] == '#') continue;

            std::stringstream stream(line);
            std::string chunk;
            Pair pair{};
            bool valid = true;

            // Parse time stamp
            if (stream >> chunk) {
                try {
                    int time_stamp = std::stoi(chunk);
                    if (time_stamp > 0) {
                        pair.time_stamp_ns = time_stamp;
                    } else {
                        valid = false;
                    }
                } catch (...) {
                    valid = false;
                }
            } else {
                valid = false;
            }

            // Parse value
            if (valid && stream >> chunk) {
                try {
                    int value = std::stoi(chunk);
                    if (value == 0 || value == 1) {
                        pair.value = (uint8_t)value;
                    } else {
                        valid = false;
                    }
                } catch (...) {
                    valid = false;
                }
            } else {
                valid = false;
            }

            // Validate ordering and append
            if (valid) {
                if (pairs.empty() || pair.time_stamp_ns > previousPair.time_stamp_ns) {
                    pairs.push_back(pair);
                    previousPair = pair;
                } else {
                    throw std::runtime_error("[ERROR] Input time stamps are not strictly increasing");
                }
            }
        }
    }

} // namespace verisim_ns
