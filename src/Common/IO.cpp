#include <fstream>
#include "Common/IO.h"

namespace virgo::common {
    std::optional<std::string> ReadFile(const std::string &filepath) {
        std::ifstream file;
        file.exceptions(std::ifstream::failbit);

        try {
            file.open(filepath, std::ios::in);
        } catch (...) {
            return std::nullopt;
        }

        auto contents = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        file.close();

        return contents;
    }
}

