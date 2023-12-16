#include "diagnostic/Diagnostic.h"

namespace virgo::diagnostic {
    auto Severity::ToString() const -> const char * {
        switch (this->value) {
            case Value::Error:
                return "error";
            case Value::Warning:
                return "warning";
            case Value::Info:
                return "info";
            case Value::Note:
                return "note";
        }
    }
}

