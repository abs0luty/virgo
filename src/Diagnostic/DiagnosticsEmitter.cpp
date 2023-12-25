#include "Diagnostic/DiagnosticsEmitter.h"

namespace virgo::diagnostic {
    auto DiagnosticEmitter::WithColor(bool withColor) -> void {
        throw std::runtime_error("Not implemented");
    }

    auto DiagnosticEmitter::WithSeverity(Severity severity) -> void {
        throw std::runtime_error("Not implemented");
    }

    auto DiagnosticEmitter::WithStream(std::ostream& stream) -> void {
        throw std::runtime_error("Not implemented");
    }

    auto DiagnosticEmitter::Emit(const virgo::diagnostic::Diagnostic &diagnostic) const -> void {
        throw std::runtime_error("Not implemented");
    }
}
