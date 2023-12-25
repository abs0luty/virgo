#include "Common/ByteLocation.h"

namespace virgo::common {
    auto PrintTo(const ByteLocation &location, std::ostream *stream) -> void {
        *stream << "ByteLocation(line: " << location.line
                << ", column: " << location.column
                << ", offset: " << location.offset
                << ")";
    }
}
