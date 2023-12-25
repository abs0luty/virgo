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
            Info,
            Note
        };

        /* implicit */ Severity(Value value) : value(value) {}

        explicit constexpr operator Value() const { return value; }

        [[nodiscard]] constexpr auto ToString() const -> const char * {
            switch (value) {
                case Error:
                    return "error";
                case Warning:
                    return "warning";
                case Info:
                    return "info";
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
        std::optional<std::string> filepath;

        /**
         * The diagnostic message.
         */
        std::string message;

        /**
         * The location in file in which the diagnostic occurred.
         */
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
        Diagnostic(Severity severity, std::string&& message,
                   std::optional<std::string> filepath,
                   std::optional<common::Span> span) :
                severity(severity), message(std::move(message)),
                filepath(std::move(filepath)), span(span) {}
    };
}

#endif //VIRGO_DIAGNOSTIC_H
