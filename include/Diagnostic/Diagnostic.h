#ifndef VIRGO_DIAGNOSTIC_H
#define VIRGO_DIAGNOSTIC_H

#include <string>
#include <optional>
#include "common/Span.h"

namespace virgo::diagnostic {
    /*!
     * A severity of a diagnostic.
     *
     * @see Diagnostic
     */
    struct Severity final {
        enum Value {
            Error,
            Warning,
            Note
        };

        /* implicit */ Severity(Value value) : value(value) {}

        /* implicit */ constexpr operator Value() const { return value; }

        [[nodiscard]] constexpr auto ToString() const -> const char * {
            switch (value) {
                case Error:
                    return "error";
                case Warning:
                    return "warning";
                case Note:
                    return "note";
            }
        }

    private:
        Value value;
    };

    /*!
     * A data structure that represents a compiler diagnostic.
     */
    struct Diagnostic final {
    public:
        /**
         * The severity of the diagnostic.
         */
        Severity severity;

        /**
         * The file in which the diagnostic occurred.
         */
        std::optional<std::string_view> filepath;

        /**
         * The diagnostic message.
         */
        std::string message;

        /**
         * The location in file in which the diagnostic occurred.
         */
        std::optional<common::Span> span;

        Diagnostic(const Diagnostic& other) = default;
        Diagnostic(Diagnostic&& other) = default;

        Diagnostic(Severity severity, std::string message) :
                severity(severity), message(std::move(message)) {}

        Diagnostic(Severity severity, std::string message,
                   std::string_view filepath) :
                severity(severity), message(std::move(message)),
                filepath(filepath) {}

        Diagnostic(Severity severity, std::string message,
                   std::string_view filepath, common::Span span) :
                severity(severity), message(std::move(message)),
                filepath(filepath), span(span) {}

        Diagnostic(Severity severity, std::string message,
                   std::optional<std::string_view> filepath,
                   std::optional<common::Span> span) :
                severity(severity), message(std::move(message)),
                filepath(filepath), span(span) {}
    };
}

#endif //VIRGO_DIAGNOSTIC_H
