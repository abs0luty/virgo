#ifndef VIRGO_STRINGHASH_H
#define VIRGO_STRINGHASH_H

#include <cstdint>

namespace virgo::intern {
    struct StringHash {
    public:
        using Hash = std::uint64_t;

        StringHash() = delete;

        StringHash(const char *) = delete;

        static auto Get(const char *) noexcept -> Hash;
        static auto Get(const char *, std::size_t) noexcept -> Hash;

    private:
        static const int seed = 131;
    };
}

#endif //VIRGO_STRINGHASH_H
