/*!
 * Provides utility functions for working with UTF8 strings and
 * individual Unicode code points.
 */

#ifndef VIRGO_ENCODING_H
#define VIRGO_ENCODING_H

#include <optional>
#include <string_view>

namespace virgo::common {
    /*!
     * Iterator over UTF8 string's individual unicode code
     * points
     */
    class Utf8StringIterator final {
    public:
        explicit Utf8StringIterator(std::string_view string)
            : string(string) {}

        /**
         * @brief   Returns the next Unicode codepoint in the string, advancing
         *          the state of the iterator
         * @return  The next Unicode codepoint in the string, or std::nullopt
         *          (denotes EOF)
         */
        auto NextCodePoint() -> std::optional<char32_t>;

    private:
        std::string_view string;
        std::size_t byteOffset = 0;
    };

    /**
     * @param  codepoint Unicode codepoint
     * @return true if the codepoint is a decimal digit
     *         false otherwise
     */
    constexpr auto IsAsciiDecimalDigit(char32_t codepoint) -> bool {
        return codepoint >= '0' && codepoint <= '9';
    }

    /**
     * @param  codepoint Unicode codepoint
     * @return true if the codepoint is not a nullopt and its value is a decimal digit
     *         false otherwise
     */
    constexpr auto IsAsciiDecimalDigit(std::optional<char32_t> codepoint) -> bool {
        return codepoint && IsAsciiDecimalDigit(*codepoint);
    }

    /**
     * @param  codepoint Unicode codepoint
     * @return true if the codepoint is a hexadecimal digit
     *         false otherwise
     */
    constexpr auto IsAsciiHexadecimalDigit(char32_t codepoint) -> bool {
        return IsAsciiDecimalDigit(codepoint)
               || (codepoint >= 'a' && codepoint <= 'f')
               || (codepoint >= 'A' && codepoint <= 'F');
    }

    /**
     * @param  codepoint Unicode codepoint
     * @return true if the codepoint is not a nullopt and its value is a hexadecimal digit
     *         false otherwise
     */
    constexpr auto IsAsciiHexadecimalDigit(std::optional<char32_t> codepoint) -> bool {
        return codepoint && IsAsciiHexadecimalDigit(*codepoint);
    }

    /**
     * @param  codepoint Unicode codepoint
     * @return true if the codepoint is an ASCII character
     *         false otherwise
     */
    constexpr auto IsAscii(char32_t codepoint) -> bool {
        return codepoint <= 127;
    }

    /**
     * @param  codepoint Unicode codepoint
     * @return true if the codepoint is not a nullopt and its value is an ASCII character
     *         false otherwise
     */
    constexpr auto IsAscii(std::optional<char32_t> codepoint) -> bool {
        return codepoint && IsAscii(*codepoint);
    }

    /**
     * @param  codepoint Unicode codepoint
     * @return true if the codepoint is a whitespace character
     *         false otherwise
     */
    constexpr auto IsWhitespace(char32_t codepoint) -> bool {
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

    /**
     * @param  codepoint Unicode codepoint
     * @return true if the codepoint is not a nullopt and its value is a whitespace character
     *         false otherwise
     */
    constexpr auto IsWhitespace(std::optional<char32_t> codepoint) -> bool {
        return codepoint && IsWhitespace(*codepoint);
    }

    /**
     * @param  codepoint Unicode codepoint
     * @return true if the codepoint is a character in XID_Start lexical class
     *         false otherwise
     * @todo   Add support for Unicode Standard Anex #31.
     */
    constexpr auto IsXIDStart(char32_t codepoint) -> bool {
        return (codepoint >= 'a' && codepoint <= 'z')
           || (codepoint >= 'A' && codepoint <= 'Z')
           || codepoint == '_';
    }

    /**
     * @param  codepoint Unicode codepoint
     * @return true if the codepoint is not a nullopt and its value is a
     *         character in XID_Start lexical class
     *         false otherwise
     */
    constexpr auto IsXIDStart(std::optional<char32_t> codepoint) -> bool {
        return codepoint && IsXIDStart(*codepoint);
    }

    /**
     * @param  codepoint Unicode codepoint
     * @return true if the codepoint is a character in XID_Continue lexical class
     *         false otherwise
     * @todo   Add support for Unicode Standard Anex #31.
     */
    constexpr auto IsXIDContinue(char32_t codepoint) -> bool {
        return (codepoint >= 'a' && codepoint <= 'z')
           || (codepoint >= 'A' && codepoint <= 'Z')
           || IsAsciiDecimalDigit(codepoint)
           || codepoint == '_';
    }

    /**
     * @param  codepoint Unicode codepoint
     * @return true if the codepoint is not a nullopt and its value is a
     *         character in XID_Continue lexical class
     *         false otherwise
     */
    constexpr auto IsXIDContinue(std::optional<char32_t> codepoint) -> bool {
        return codepoint && IsXIDContinue(*codepoint);
    }
}

#endif //VIRGO_ENCODING_H
