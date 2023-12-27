#ifndef VIRGO_ERROR_H
#define VIRGO_ERROR_H

#include <optional>
#include <string>
#include "Common/Span.h"
#include "Diagnostic/Diagnostic.h"

namespace virgo::common {
    /*!
     * Global compiler error (mostly used for CLI)
     */
    class Error : public std::exception {
    public:
        /**
         * Location of the error in the file (optional)
         */
        std::optional<common::Span> span;

        /**
         * The file in which the error occurred (optional)
         */
        std::string_view filepath;

        /**
         * The error message
         */
        std::string message;

        // Global compiler error
        explicit Error(std::string message)
                : message(std::move(message)) {}

        // Filepath is specified
        Error(std::string message, std::string_view filepath)
                : message(std::move(message)), filepath(filepath) {}

        // Span is also specified
        Error(std::string message, std::string_view filepath, common::Span span)
                : message(std::move(message)), filepath(filepath), span(span) {}

        [[nodiscard]] auto what() const -> const char * override {
            return message.c_str();
        }

        /**
         * @brief  Converts the error to a diagnostic that can be later emitted
         *         by fancy diagnostics emitter
         * @return The diagnostic struct
         */
        auto ToDiagnostic() -> diagnostic::Diagnostic {
            return diagnostic::Diagnostic {
                diagnostic::Severity::Error,
                std::move(message),
                filepath,
                span
            };
        }

        ~Error() override {
            message.~basic_string();
        }
    };
}

#endif //VIRGO_ERROR_H
