#ifndef VIRGO_CODEPOINTS_ITERATOR_H
#define VIRGO_CODEPOINTS_ITERATOR_H

#include <string>
#include <optional>
#include "Common/Span.h"

namespace virgo::common {
    class CodePointsIterator final {
    public:
        explicit CodePointsIterator(const std::string& string) : string(string) {}

        auto NextCodePoint() -> std::optional<char32_t>;

    private:
        const std::string& string;
        std::size_t offset = 0;
    };
}

#endif //VIRGO_CODEPOINTS_ITERATOR_H
