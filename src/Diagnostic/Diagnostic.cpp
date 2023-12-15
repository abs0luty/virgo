#include "diagnostic/Diagnostic.h"

namespace virgo::diagnostic {
    auto Severity::ToString() const noexcept -> const char * {
        switch (severity) {
            case SeverityEnum::Error:
                return "error";
            case SeverityEnum::Warning:
                return "warning";
            case SeverityEnum::Info:
                return "info";
            case SeverityEnum::Note:
                return "note";
        }
    }

    auto Severity::Error() noexcept -> Severity {
        return {SeverityEnum::Error};
    }

    auto Severity::Info() noexcept -> Severity {
        return {SeverityEnum::Info};
    }

    auto Severity::Note() noexcept -> Severity {
        return {SeverityEnum::Note};
    }

    auto Severity::Warning() noexcept -> Severity {
        return {SeverityEnum::Warning};
    }
}

