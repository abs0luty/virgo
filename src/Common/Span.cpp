#include "common/Span.h"

namespace virgo::common {
    const ByteLocation ByteLocation::kDummy = {0, 0, 0};

    auto ByteLocation::IsDummy() const noexcept -> bool {
        return this == &kDummy;
    }

    auto ByteLocation::WithRelativeOffset(OffsetType relativeOffset) const noexcept -> ByteLocation {
        return {line, column + relativeOffset, offset + relativeOffset};
    }

    auto ByteLocation::NextByteLocation() const noexcept -> ByteLocation {
        return WithRelativeOffset(1);
    }

    auto ByteLocation::NextSecondByteLocation() const noexcept -> ByteLocation {
        return WithRelativeOffset(2);
    }

    auto ByteLocation::operator==(const ByteLocation &other) const noexcept -> bool {
        return line == other.line && column == other.column && offset == other.offset;
    }

    auto ByteLocation::StartOfFile() noexcept -> ByteLocation {
        return {1, 0, 0};
    }

    const Span Span::kDummy = {ByteLocation::kDummy, ByteLocation::kDummy};

    auto Span::SingleByteSpan(ByteLocation location) -> Span {
        return {location, location.NextByteLocation()};
    }

    auto Span::TwoSuccessiveBytesSpan(ByteLocation location) -> Span {
        return {location, location.NextSecondByteLocation()};
    }

    auto Span::Length() const noexcept -> common::OffsetType {
        return end.offset - start.offset;
    }

    auto Span::IsDummy() const noexcept -> bool {
        return this == &kDummy;
    }

    auto Span::operator==(const Span &other) const noexcept -> bool {
        return start == other.start && end == other.end;
    }
}
