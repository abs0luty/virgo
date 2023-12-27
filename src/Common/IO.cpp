#include <fstream>
#include "Common/IO.h"

namespace virgo::common {
    std::string ReadFile(std::string_view filepath) {
        std::ifstream file;
        file.exceptions(std::ifstream::failbit);

        try {
            file.open(filepath.data(), std::ios::in);
        } catch (...) {
            throw FailedToReadFileError(filepath);
        }

        auto contents = std::string(
                std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>()
        );
        file.close();

        return contents;
    }
}
