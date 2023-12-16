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
        [[nodiscard]] static auto constexpr StartOfFile() -> ByteLocation {
            return {1, 0, 0};
        }

        // Returns true if the location is dummy.
        [[nodiscard]] auto constexpr IsDummy() const -> bool {
            return this == &kDummy;
        }

        // Returns the location shifted by the given relative offset.
        // Note: the column here is also changed, while the line number isn't.
        [[nodiscard]] auto constexpr WithRelativeOffset(std::size_t relativeOffset) const -> ByteLocation {
            return {line, column + relativeOffset, offset + relativeOffset};
        }

        // Returns the location of the next byte relative to the current one.
        [[nodiscard]] auto constexpr NextByteLocation() const -> ByteLocation {
            return WithRelativeOffset(1);
        }

        // Returns the location of the next second byte relative to the
        // current one.
        [[nodiscard]] auto constexpr NextSecondByteLocation() const -> ByteLocation {
            return WithRelativeOffset(2);
        }

        [[nodiscard]] auto constexpr operator==(const ByteLocation& other) const -> bool {
            return line == other.line
                && column == other.column
                && offset == other.offset;
        }

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
        [[nodiscard]] static constexpr auto SingleByteSpan(ByteLocation location) -> Span {
            return {location, location.NextByteLocation()};
        }

        // Returns a span consisting of two successive bytes.
        [[nodiscard]] static constexpr auto TwoSuccessiveBytesSpan(ByteLocation location) -> Span {
            return {location, location.NextSecondByteLocation()};
        }

        // Returns the length of the span (amount of bytes in it).
        [[nodiscard]] auto constexpr Length() const -> std::size_t {
            return end.offset - start.offset;
        }

        // Returns true if the span is dummy.
        [[nodiscard]] auto constexpr IsDummy() const -> bool {
            return this == &kDummy;
        }

        [[nodiscard]] auto constexpr operator==(const Span& other) const -> bool {
            return start == other.start && end == other.end;
        }

        // Returns true if the span is not dummy.
        explicit operator bool() const {
            return !IsDummy();
        }
    };

    const ByteLocation ByteLocation::kDummy = {0, 0, 0};
    const Span Span::kDummy = {ByteLocation::kDummy, ByteLocation::kDummy};
}

#endif //VIRGO_SPAN_H
