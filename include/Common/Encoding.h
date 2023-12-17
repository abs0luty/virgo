#ifndef VIRGO_ENCODING_H
#define VIRGO_ENCODING_H

namespace virgo::common {
    [[nodiscard]] auto constexpr IsAsciiDecimalDigit(char32_t codepoint) -> bool {
        return codepoint >= '0' && codepoint <= '9';
    }

    [[nodiscard]] auto constexpr IsAsciiDecimalDigit(std::optional<char32_t> codepoint) -> bool {
        return codepoint && IsAsciiDecimalDigit(*codepoint);
    }

    [[nodiscard]] auto constexpr IsAsciiHexadecimalDigit(char32_t codepoint) -> bool {
        return IsAsciiDecimalDigit(codepoint)
               || (codepoint >= 'a' && codepoint <= 'f')
               || (codepoint >= 'A' && codepoint <= 'F');
    }

    [[nodiscard]] auto constexpr IsAsciiHexadecimalDigit(std::optional<char32_t> codepoint) -> bool {
        return codepoint && IsAsciiHexadecimalDigit(*codepoint);
    }

    [[nodiscard]] auto constexpr IsAscii(char32_t codepoint) -> bool {
        return codepoint <= 127;
    }

    [[nodiscard]] auto constexpr IsAscii(std::optional<char32_t> codepoint) -> bool {
        return codepoint && IsAscii(*codepoint);
    }

    [[nodiscard]] auto constexpr IsWhitespace(char32_t codepoint) -> bool {
        return codepoint == 0x0009     // \t
               || codepoint == 0x000a  // \n
               || codepoint == 0x000b  // vertical tab
               || codepoint == 0x000c  // form feed
               || codepoint == 0x000d  // \r
               || codepoint == 0x0020  // space
               // NEXT LINE from latin1
               || codepoint == 0x0085
               // Bidi markers
               || codepoint == 0x200e  // LEFT-TO-RIGHT MARK
               || codepoint == 0x200f  // RIGHT-TO-LEFT MARK
               // Dedicated whitespace characters from Unicode
               || codepoint == 0x2028  // LINE SEPARATOR
               || codepoint == 0x2029; // PARAGRAPH SEPARATOR
    }

    [[nodiscard]] auto constexpr IsWhitespace(std::optional<char32_t> codepoint) -> bool {
        return codepoint && IsWhitespace(*codepoint);
    }

    // TODO: Add support for Unicode Standard Anex #31.
    [[nodiscard]] auto constexpr IsXIDStart(char32_t codepoint) -> bool {
        return (codepoint >= 'a' && codepoint <= 'z')
           || (codepoint >= 'A' && codepoint <= 'Z')
           || codepoint == '_';
    }

    [[nodiscard]] auto constexpr IsXIDStart(std::optional<char32_t> codepoint) -> bool {
        return codepoint && IsXIDStart(*codepoint);
    }

    // TODO: Add support for Unicode Standard Anex #31.
    [[nodiscard]] auto constexpr IsXIDContinue(char32_t codepoint) -> bool {
        return (codepoint >= 'a' && codepoint <= 'z')
           || (codepoint >= 'A' && codepoint <= 'Z')
           || IsAsciiDecimalDigit(codepoint)
           || codepoint == '_';
    }

    [[nodiscard]] auto constexpr IsXIDContinue(std::optional<char32_t> codepoint) -> bool {
        return codepoint && IsXIDContinue(*codepoint);
    }
}

#endif //VIRGO_ENCODING_H
