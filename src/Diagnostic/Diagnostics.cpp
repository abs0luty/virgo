#include "Diagnostic/Diagnostics.h"

namespace virgo::diagnostic {
    auto Diagnostics::AddDiagnostic(const virgo::diagnostic::Diagnostic &diagnostic) -> void {
        diagnostics.push_back(diagnostic);
    }

    auto Diagnostics::AddDiagnostic(Diagnostic &&diagnostic) -> void {
        diagnostics.push_back(std::move(diagnostic));
    }

    auto Diagnostics::Clear() -> void {
        diagnostics.clear();
    }
}
