#ifndef VIRGO_DIAGNOSTICS_H
#define VIRGO_DIAGNOSTICS_H

#include <vector>
#include "Diagnostic/Diagnostic.h"
#include "Diagnostic/DiagnosticsEmitter.h"

namespace virgo::diagnostic {
    class Diagnostics final {
    public:
        Diagnostics() {}

        auto AddDiagnostic(const Diagnostic& diagnostic) -> void;
        auto AddDiagnostic(Diagnostic &&diagnostic) -> void;
        auto Clear() -> void;

        ~Diagnostics() = default;

    private:
        std::vector<Diagnostic> diagnostics;
    };
}

#endif //VIRGO_DIAGNOSTICS_H
