#ifndef VIRGO_SPAN_H
#define VIRGO_SPAN_H

#include <cstddef>

namespace virgo::span {
    struct ByteLocation {
    public:
        using OffsetType = std::size_t;

        static const ByteLocation kDummy;

        OffsetType line, column, offset;

        ByteLocation(OffsetType line, OffsetType column, OffsetType offset)
                : line(line), column(column), offset(offset) {}

        [[nodiscard]] auto IsDummy() const noexcept -> bool;

        [[nodiscard]] auto NextByteLocation() const noexcept -> ByteLocation;

        auto operator==(const ByteLocation&) const noexcept -> bool;

        explicit operator bool() const noexcept {
            return !IsDummy();
        }
    };

    struct Span {
    public:
        static const Span kDummy;

        ByteLocation start, end;

        Span(ByteLocation start, ByteLocation end) : start(start), end(end) {}

        static auto SingleByteSpan(ByteLocation) -> Span;

        [[nodiscard]] auto Length() const noexcept -> size_t;

        [[nodiscard]] auto IsDummy() const noexcept -> bool;

        auto operator==(const Span&) const noexcept -> bool;

        explicit operator bool() const noexcept {
            return !IsDummy();
        }
    };
}

#endif //VIRGO_SPAN_H
