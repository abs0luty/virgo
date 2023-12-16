#ifndef VIRGO_ENCODING_H
#define VIRGO_ENCODING_H

namespace virgo::common {
    [[nodiscard]] auto constexpr IsAsciiDecimalDigit(char32_t) noexcept -> bool;
    [[nodiscard]] auto constexpr IsAsciiHexadecimalDigit(char32_t) noexcept -> bool;
    [[nodiscard]] auto constexpr IsAscii(char32_t) noexcept -> bool;
    [[nodiscard]] auto constexpr IsAsciiWordCharacter(char32_t) noexcept -> bool;
    [[nodiscard]] auto constexpr IsAsciiWhitespace(char32_t) noexcept -> bool;
    [[nodiscard]] auto constexpr IsUtf8XIDStart(char32_t) noexcept -> bool;
    [[nodiscard]] auto constexpr IsUtf8XIDContinue(char32_t) noexcept -> bool;
}

#endif //VIRGO_ENCODING_H
