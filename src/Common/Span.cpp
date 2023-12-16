#include "common/Span.h"

namespace virgo::common {
    const ByteLocation ByteLocation::kDummy = {0, 0, 0};

    auto constexpr ByteLocation::IsDummy() const -> bool {
        return this == &kDummy;
    }

    auto constexpr ByteLocation::WithRelativeOffset(std::size_t relativeOffset) const -> ByteLocation {
        return {line, column + relativeOffset, offset + relativeOffset};
    }

    auto constexpr ByteLocation::NextByteLocation() const -> ByteLocation {
        return WithRelativeOffset(1);
    }

    auto constexpr ByteLocation::NextSecondByteLocation() const -> ByteLocation {
        return WithRelativeOffset(2);
    }

    auto ByteLocation::operator==(const ByteLocation &other) const -> bool {
        return line == other.line && column == other.column && offset == other.offset;
    }

    auto constexpr ByteLocation::StartOfFile() -> ByteLocation {
        return {1, 0, 0};
    }

    const Span Span::kDummy = {ByteLocation::kDummy, ByteLocation::kDummy};

    auto constexpr Span::SingleByteSpan(ByteLocation location) -> Span {
        return {location, location.NextByteLocation()};
    }

    auto constexpr Span::TwoSuccessiveBytesSpan(ByteLocation location) -> Span {
        return {location, location.NextSecondByteLocation()};
    }

    auto constexpr Span::Length() const -> common::std::size_t {
        return end.offset - start.offset;
    }

    auto constexpr Span::IsDummy() const -> bool {
        return this == &kDummy;
    }

    auto Span::operator==(const Span &other) const -> bool {
        return start == other.start && end == other.end;
    }
}
