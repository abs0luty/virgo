#ifndef VIRGO_DIAGNOSTIC_H
#define VIRGO_DIAGNOSTIC_H

#include <string>
#include <optional>
#include "common/Span.h"

namespace virgo::diagnostic {
    struct Severity final {
        enum Value {
            Error,
            Warning,
            Info,
            Note
        };
    public:
        [[nodiscard]] auto ToString() const -> const char *;
    private:
        Value value;
    };

    class Diagnostic final {
    public:
        // The severity of the diagnostic.
        Severity severity;

        // The file in which the diagnostic occurred.
        std::optional<std::string> filepath;

        // The diagnostic message.
        std::string message;

        // Location in which the diagnostic occurred.
        std::optional<common::Span> span;

        Diagnostic(Severity severity, std::string&& message) :
                severity(severity), message(std::move(message)) {}
        Diagnostic(Severity severity, std::string&& message,
                   const std::string& filepath) :
                severity(severity), message(std::move(message)),
                filepath(filepath) {}
        Diagnostic(Severity severity, std::string&& message,
                   const std::string& filepath, common::Span span) :
                severity(severity), message(std::move(message)),
                filepath(filepath), span(span) {}
    };
}

#endif //VIRGO_DIAGNOSTIC_H
