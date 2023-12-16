#include "Common/CodePointsIterator.h"

namespace virgo::common {
    auto CodePointsIterator::NextCodePoint() -> std::optional<char32_t> {
        if (offset >= string.size()) {
            return std::nullopt;
        }

        char32_t codePoint = 0;

        unsigned char firstByte = string[offset++];

        if (firstByte < 0x80) {
            codePoint = firstByte;
        } else if (firstByte < 0xE0) {
            codePoint = firstByte & 0x1F;
            codePoint = (codePoint << 6) | (string[offset++] & 0x3F);
        } else if (firstByte < 0xF0) {
            codePoint = firstByte & 0x0F;
            codePoint = (codePoint << 6) | (string[offset++] & 0x3F);
            codePoint = (codePoint << 6) | (string[offset++] & 0x3F);
        } else {
            codePoint = firstByte & 0x07;
            codePoint = (codePoint << 6) | (string[offset++] & 0x3F);
            codePoint = (codePoint << 6) | (string[offset++] & 0x3F);
            codePoint = (codePoint << 6) | (string[offset++] & 0x3F);
        }

        return codePoint;
    }
}