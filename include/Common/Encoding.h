#ifndef VIRGO_ENCODING_H
#define VIRGO_ENCODING_H

namespace virgo::common {
    [[nodiscard]] auto constexpr IsAsciiDecimalDigit(char32_t codepoint) -> bool {
        return codepoint >= '0' && codepoint <= '9';
    }

    [[nodiscard]] auto constexpr IsAsciiHexadecimalDigit(char32_t codepoint) -> bool {
        return IsAsciiDecimalDigit(codepoint)
               || (codepoint >= 'a' && codepoint <= 'f')
               || (codepoint >= 'A' && codepoint <= 'F');
    }

    [[nodiscard]] auto constexpr IsAscii(char32_t codepoint) -> bool {
        return codepoint <= 127;
    }

    [[nodiscard]] auto constexpr IsAsciiWordCharacter(char32_t codepoint) -> bool {
        return IsAsciiDecimalDigit(codepoint)
               || (codepoint >= 'a' && codepoint <= 'z')
               || (codepoint >= 'A' && codepoint <= 'Z')
               || codepoint == '_';
    }

    [[nodiscard]] auto constexpr IsAsciiWhitespace(char32_t codepoint) -> bool {
        return codepoint == ' '
               || codepoint == '\t'
               || codepoint == '\n'
               || codepoint == '\r';
    }
}

#endif //VIRGO_ENCODING_H
