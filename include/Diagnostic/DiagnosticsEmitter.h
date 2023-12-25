#ifndef VIRGO_DIAGNOSTICSEMITTER_H
#define VIRGO_DIAGNOSTICSEMITTER_H

#include <iostream>
#include "Diagnostic/Diagnostic.h"

namespace virgo::diagnostic {
    class DiagnosticEmitter final {
    public:
        bool withColor = true;
        Severity severity = Severity::Note;
        std::ostream& stream = std::cout;

        constexpr DiagnosticEmitter() = default;

        auto WithColor(bool withColor) -> void;
        auto WithSeverity(Severity severity) -> void;
        auto WithStream(std::ostream& stream) -> void;

        auto Emit(const Diagnostic &diagnostic) const -> void;
    };
}

#endif //VIRGO_DIAGNOSTICSEMITTER_H
