#ifndef VIRGO_SPAN_H
#define VIRGO_SPAN_H

#include <cstddef>

namespace virgo::common {
    struct ByteLocation final {
        // Dummy value of byte location, which can be used as
        // a placeholder in tests.
        static const ByteLocation kDummy;

        std::size_t line, column, offset;

        // Returns the location of the byte located at the start
        // of the file.
        [[nodiscard]] static auto constexpr StartOfFile() -> ByteLocation;

        // Returns true if the location is dummy.
        [[nodiscard]] auto constexpr IsDummy() const -> bool;

        // Returns the location shifted by the given relative offset.
        // Note: the column here is also changed, while the line number isn't.
        [[nodiscard]] auto constexpr WithRelativeOffset(std::size_t) const -> ByteLocation;

        // Returns the location of the next byte relative to the current one.
        [[nodiscard]] auto constexpr NextByteLocation() const -> ByteLocation;

        // Returns the location of the next second byte relative to the
        // current one.
        [[nodiscard]] auto constexpr NextSecondByteLocation() const -> ByteLocation;

        auto operator==(const ByteLocation&) const -> bool;

        // Returns true if the location is not dummy.
        explicit operator bool() const {
            return !IsDummy();
        }
    };

    struct Span final {
        // Dummy value of span, which can be used as a placeholder
        // in tests.
        static const Span kDummy;

        ByteLocation start, end;

        // Returns a span consisting of a single byte.
        [[nodiscard]] static constexpr auto SingleByteSpan(ByteLocation) -> Span;

        // Returns a span consisting of two successive bytes.
        [[nodiscard]] static constexpr auto TwoSuccessiveBytesSpan(ByteLocation) -> Span;

        // Returns the length of the span (amount of bytes in it).
        [[nodiscard]] auto constexpr Length() const -> std::size_t;

        // Returns true if the span is dummy.
        [[nodiscard]] auto constexpr IsDummy() const -> bool;

        auto operator==(const Span&) const -> bool;

        // Returns true if the span is not dummy.
        explicit operator bool() const {
            return !IsDummy();
        }
    };
}

#endif //VIRGO_SPAN_H
