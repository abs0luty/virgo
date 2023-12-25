#include <iostream>
#include "Common/Span.h"

namespace virgo::common {
    auto PrintTo(const Span &span, std::ostream *stream) -> void {
        *stream << "Span(start: ";
        PrintTo(span.start, stream);
        *stream << ", end: ";
        PrintTo(span.end, stream);
        *stream << ")";
    }
}
