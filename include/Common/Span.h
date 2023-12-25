#ifndef VIRGO_SPAN_H
#define VIRGO_SPAN_H

#include <cstddef>
#include "Common/ByteLocation.h"

namespace virgo::common {
    /*!
     * A data structure representing a span of bytes in a source file.
     */
    struct Span final {
        ByteLocation start, end;

        /**
         * @return a dummy value of span, which can be used as a placeholder
         *         in tests
         * @note   <b>!!!
         *         THIS SHOULD NOT BE USED IN ANY ACTUAL COMPILER'S CODE OTHER
         *         THAN TESTS !!!</b>
         */
        static constexpr auto Dummy() -> Span {
            return {ByteLocation::Dummy(), ByteLocation::Dummy()};
        }

        /**
         * @param  location the location of the byte
         * @return a span containing only the given byte
         */
        static constexpr auto SingleByteSpan(const ByteLocation& location) -> Span {
            return {location, location.NextByteLocation()};
        }

        /**
         * @param  location the location of the first byte
         * @return a span consisting of two successive bytes
         */
        static constexpr auto TwoSuccessiveBytesSpan(const ByteLocation& location) -> Span {
            return {location, location.NextSecondByteLocation()};
        }

        /**
         * @param  location    the location of the first byte
         * @param  bytesAmount the amount of bytes in the span
         * @return a span consisting of multiple successive bytes
         */
        static constexpr auto MultipleSuccessiveBytesSpan(
                const ByteLocation& location,
                std::size_t bytesAmount) -> Span {
            return {location, location.WithRelativeOffset(bytesAmount)};
        }

        /**
         * @return the length of the span (amount of bytes in it)
         */
        [[nodiscard]] constexpr auto Length() const -> std::size_t {
            return end.offset - start.offset;
        }

        /**
         * @return true if the span is dummy
         *         false otherwise
         */
        [[nodiscard]] constexpr auto IsDummy() const -> bool {
            auto dummy = Dummy();
            return this == &dummy;
        }

        constexpr auto operator==(const Span& other) const -> bool {
            return start == other.start && end == other.end;
        }

        // Returns true if the span is not dummy.
        explicit operator bool() const {
            return !IsDummy();
        }
    };

    auto PrintTo(const Span &span, std::ostream *stream) -> void;
}

#endif //VIRGO_SPAN_H
