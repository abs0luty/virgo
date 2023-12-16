#include "Common/Encoding.h"

namespace virgo::common {
    auto constexpr IsAsciiDecimalDigit(char32_t codepoint) noexcept -> bool {
        return codepoint >= '0' && codepoint <= '9';
    }

    auto constexpr IsAsciiHexadecimalDigit(char32_t codepoint) noexcept -> bool {
        return IsAsciiDecimalDigit(codepoint)
            || (codepoint >= 'a' && codepoint <= 'f')
            || (codepoint >= 'A' && codepoint <= 'F');
    }

    auto constexpr IsAscii(char32_t codepoint) noexcept -> bool {
        return codepoint <= 127;
    }

    auto constexpr IsAsciiWordCharacter(char32_t codepoint) noexcept -> bool {
        return IsAsciiDecimalDigit(codepoint)
           || (codepoint >= 'a' && codepoint <= 'z')
           || (codepoint >= 'A' && codepoint <= 'Z')
           || codepoint == '_';
    }

    auto constexpr IsAsciiWhitespace(char32_t codepoint) noexcept -> bool {
        return codepoint == ' '
            || codepoint == '\t'
            || codepoint == '\n'
            || codepoint == '\r';
    }
}
