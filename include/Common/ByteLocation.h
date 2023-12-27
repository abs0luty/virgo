#ifndef VIRGO_BYTELOCATION_H
#define VIRGO_BYTELOCATION_H

#include <cstddef>
#include <ostream>

namespace virgo::common {
    /*!
     * A data structure that represents a location of individual byte
     * in a source file.
     */
    struct ByteLocation final {
        std::size_t line, column, offset;

        /**
         * @return a dummy value of byte location, which can be used as
         * a placeholder in tests
         * @note   <b>!!!
         *         THIS SHOULD NOT BE USED IN ANY ACTUAL COMPILER'S CODE OTHER
         *         THAN TESTS !!!</b>
         */
        static constexpr auto Dummy() -> ByteLocation {
            return {0, 0, 0};
        }

        /**
         * @return the location of the byte located at the start
         *         of the file
         */
        static constexpr auto StartOfFile() -> ByteLocation {
            return {1, 0, 0};
        }

        /**
         * @return true if the location is dummy
         *         false otherwise
         */
        [[nodiscard]] constexpr auto IsDummy() const -> bool {
            auto dummy = Dummy();
            return this == &dummy;
        }

        /**
         * @param  relativeOffset the relative offset
         * @return the location shifted by the given relative offset
         * @note   the column here is also changed, while the line number isn't
         */
        [[nodiscard]] constexpr auto WithRelativeOffset(std::size_t relativeOffset) const -> ByteLocation {
            return {line, column + relativeOffset, offset + relativeOffset};
        }

        /**
         * @return the location of the previous byte relative to the
         *         current one
         */
        [[nodiscard]] constexpr auto OfPreviousByte() const -> ByteLocation {
            return WithRelativeOffset(-1);
        }

        /**
         * @return the location of the previous second byte relative to the
         *         current one
         */
        [[nodiscard]] constexpr auto OfPreviousSecondByte() const -> ByteLocation {
            return WithRelativeOffset(-2);
        }

        /**
         * @return the location of the next byte relative to the
         *         current one
         */
        [[nodiscard]] constexpr auto OfNextByte() const -> ByteLocation {
            return WithRelativeOffset(1);
        }

        /**
         * @return the location of the next second byte relative to the
         *         current one
         */
        [[nodiscard]] constexpr auto OfNextSecondByte() const -> ByteLocation {
            return WithRelativeOffset(2);
        }

        constexpr auto operator==(const ByteLocation &other) const -> bool {
            return line == other.line
                   && column == other.column
                   && offset == other.offset;
        }

        // Returns true if the location is not dummy.
        explicit operator bool() const {
            return !IsDummy();
        }
    };

    auto PrintTo(const ByteLocation& location, std::ostream* stream) -> void;
}

#endif //VIRGO_BYTELOCATION_H
