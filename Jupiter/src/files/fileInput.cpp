#include "fileInput.hpp"

namespace ns_jupiter
{
    FileIn::FileIn(const std::string& fileName) {
        inputFile.open(fileName);
        is_file_open = inputFile.is_open();
        fileLoad();
    }

    FileIn::~FileIn() {
        if (is_file_open) {
            inputFile.close();
        }
    }
    const std::vector<Pair>& FileIn::getPairs() const {
        return pairs;
    }

    void FileIn::fileLoad() {
        if (!inputFile.is_open()) {
            throw std::runtime_error("[ERROR] Could not open input file");
        }

        pairs.clear();  // important if reload is ever allowed

        std::string line;
        Pair previousPair{0, 0};

        while (std::getline(inputFile, line)) {
            if (line.empty() || line[0] == '#') continue;

            std::stringstream stream(line);
            std::string chunk;
            Pair pair{};
            
            // Parse time stamp
            if (!(stream >> chunk)) continue;
            try {
                int time_stamp = std::stoi(chunk, nullptr, 0); // base 0 = dec/hex/oct
                if (time_stamp <= 0) throw std::runtime_error("Invalid time");
                pair.time_stamp_ns = time_stamp;
            } catch (const std::exception& e) {
                throw std::runtime_error("[ERROR] Failed to parse time stamp in line: " + line);
            }

            // Parse value
            if (!(stream >> chunk)) continue;
            try {
                int value = std::stoi(chunk);
                if (value < 0) throw std::runtime_error("Invalid value");
                pair.value = static_cast<uint32_t>(value);
            } catch (const std::exception& e) {
                throw std::runtime_error("[ERROR] Negative value at line " + line);
            }

            // Ordering check
            if (!pairs.empty() && pair.time_stamp_ns <= previousPair.time_stamp_ns) {
                throw std::runtime_error("[ERROR] Input time stamps must be strictly increasing");
            }

            pairs.push_back(pair);
            previousPair = pair;
        }
    }

} // namespace ns_jupiter
