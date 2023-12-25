#include "Common/Encoding.h"

namespace virgo::common {
    auto Utf8StringIterator::NextCodePoint() -> std::optional<char32_t> {
        if (byteOffset >= string.size()) {
            return std::nullopt;
        }

        char32_t codePoint = 0;
        unsigned char firstByte = string[byteOffset++];

        if (firstByte < 0x80) {
            codePoint = firstByte;
        } else if (firstByte < 0xE0) {
            codePoint = firstByte & 0x1F;
            codePoint = (codePoint << 6) | (string[byteOffset++] & 0x3F);
        } else if (firstByte < 0xF0) {
            codePoint = firstByte & 0x0F;
            codePoint = (codePoint << 6) | (string[byteOffset++] & 0x3F);
            codePoint = (codePoint << 6) | (string[byteOffset++] & 0x3F);
        } else {
            codePoint = firstByte & 0x07;
            codePoint = (codePoint << 6) | (string[byteOffset++] & 0x3F);
            codePoint = (codePoint << 6) | (string[byteOffset++] & 0x3F);
            codePoint = (codePoint << 6) | (string[byteOffset++] & 0x3F);
        }

        return codePoint;
    }
}
