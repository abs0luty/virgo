#include "Intern/StringHash.h"
#include "Intern/XXHash.h"

#include <cstring>

namespace virgo::intern {
    auto StringHash::Get(const char *str) noexcept -> Hash {
        return str ? Get(str, std::strlen(str)) : 0;
    }

    auto StringHash::Get(const char *str, std::size_t length) noexcept -> Hash {
        return str ? XXH64(str, length, seed) : 0;
    }
}