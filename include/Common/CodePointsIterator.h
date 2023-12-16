#ifndef VIRGO_CODEPOINTS_ITERATOR_H
#define VIRGO_CODEPOINTS_ITERATOR_H

#include <string>
#include <optional>
#include "Common/Span.h"

namespace virgo::common {
    class CodePointsIterator final {
    public:
        CodePointsIterator() = default;

        explicit CodePointsIterator(const std::string& string) : string(string) {}
        explicit CodePointsIterator(std::string&& string) : string(std::move(string)) {}

        auto NextCodePoint() -> std::optional<char32_t>;

    private:
        std::string string;
        std::size_t offset = 0;
    };
}

#endif //VIRGO_CODEPOINTS_ITERATOR_H
