#ifndef VIRGO_SPAN_H
#define VIRGO_SPAN_H

#include <cstddef>

namespace virgo::common {
    using OffsetType = std::size_t;

    struct ByteLocation final {
        // Dummy value of byte location, which can be used as
        // a placeholder in tests.
        static const ByteLocation kDummy;

        OffsetType line, column, offset;

        // Returns the location of the byte located at the start
        // of the file.
        [[nodiscard]] static auto StartOfFile() noexcept -> ByteLocation;

        // Returns true if the location is dummy.
        [[nodiscard]] auto IsDummy() const noexcept -> bool;

        // Returns the location shifted by the given relative offset.
        // Note: the column here is also changed, while the line number isn't.
        [[nodiscard]] auto WithRelativeOffset(OffsetType) const noexcept -> ByteLocation;

        // Returns the location of the next byte relative to the current one.
        [[nodiscard]] auto NextByteLocation() const noexcept -> ByteLocation;

        // Returns the location of the next second byte relative to the
        // current one.
        [[nodiscard]] auto NextSecondByteLocation() const noexcept -> ByteLocation;

        auto operator==(const ByteLocation&) const noexcept -> bool;

        // Returns true if the location is not dummy.
        explicit operator bool() const noexcept {
            return !IsDummy();
        }
    };

    struct Span final {
        // Dummy value of span, which can be used as a placeholder
        // in tests.
        static const Span kDummy;

        ByteLocation start, end;

        // Returns a span consisting of a single byte.
        [[nodiscard]] static auto SingleByteSpan(ByteLocation) -> Span;

        // Returns a span consisting of two successive bytes.
        [[nodiscard]] static auto TwoSuccessiveBytesSpan(ByteLocation) -> Span;

        // Returns the length of the span (amount of bytes in it).
        [[nodiscard]] auto Length() const noexcept -> OffsetType;

        // Returns true if the span is dummy.
        [[nodiscard]] auto IsDummy() const noexcept -> bool;

        auto operator==(const Span&) const noexcept -> bool;

        // Returns true if the span is not dummy.
        explicit operator bool() const noexcept {
            return !IsDummy();
        }
    };
}

#endif //VIRGO_SPAN_H
