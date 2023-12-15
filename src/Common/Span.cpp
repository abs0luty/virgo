#include "common/Span.h"

namespace virgo::span {
    const ByteLocation ByteLocation::kDummy = {0, 0, 0};

    auto ByteLocation::IsDummy() const noexcept -> bool {
        return this == &kDummy;
    }

    auto ByteLocation::NextByteLocation() const noexcept -> ByteLocation {
        return {line, column, offset + 1};
    }

    auto ByteLocation::operator==(const ByteLocation &other) const noexcept -> bool {
        return line == other.line && column == other.column && offset == other.offset;
    }

    const Span Span::kDummy = {ByteLocation::kDummy, ByteLocation::kDummy};

    auto Span::SingleByteSpan(ByteLocation location) -> Span {
        return {location, location};
    }

    auto Span::Length() const noexcept -> size_t {
        return end.offset - start.offset;
    }

    auto Span::IsDummy() const noexcept -> bool {
        return this == &kDummy;
    }

    auto Span::operator==(const Span &other) const noexcept -> bool {
        return start == other.start && end == other.end;
    }
}
