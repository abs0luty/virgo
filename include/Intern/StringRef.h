#ifndef VIRGO_STRINGREF_H
#define VIRGO_STRINGREF_H

#include <cstdint>

namespace virgo::intern {
    struct StringRef {
    public:
        using Idx = std::uint32_t;

        StringRef() noexcept;
        StringRef(const StringRef&) noexcept;

        Idx Index() const noexcept;
    };
}

#endif //VIRGO_STRINGREF_H
