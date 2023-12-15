#ifndef VIRGO_DIAGNOSTIC_H
#define VIRGO_DIAGNOSTIC_H

#include <string>
#include <optional>
#include "common/Span.h"

namespace virgo::diagnostic {
    struct Severity {
        enum class SeverityEnum {
            Error,
            Warning,
            Info,
            Note
        };
        SeverityEnum severity;
    public:
        static auto Error() noexcept -> Severity;
        static auto Warning() noexcept -> Severity;
        static auto Info() noexcept -> Severity;
        static auto Note() noexcept -> Severity;

        [[nodiscard]] auto ToString() const noexcept -> const char *;
    };

    class Diagnostic {
    public:
        Severity severity;
        const char *filepath;
        std::string message;
        std::optional<span::Span> span;

        Diagnostic(Severity severity, const char *filepath,
                   const char *message)
                : severity(severity), filepath(filepath), message(message) {};

        Diagnostic(Severity severity, const char *filepath,
                   const char *message, span::Span span)
                : severity(severity), filepath(filepath), message(message),
                  span(span) {};
    };
}

#endif //VIRGO_DIAGNOSTIC_H
