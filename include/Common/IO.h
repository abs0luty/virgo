#ifndef VIRGO_IO_H
#define VIRGO_IO_H

#include <string>
#include <optional>

namespace virgo::common {
    std::optional<std::string> ReadFile(const std::string &filepath);
}

#endif //VIRGO_IO_H
