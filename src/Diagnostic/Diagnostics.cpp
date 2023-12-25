#include "Diagnostic/Diagnostics.h"

namespace virgo::diagnostic {
    auto Diagnostics::AddDiagnostic(const Diagnostic &diagnostic) -> void {
        Diagnostic copy = diagnostic;
        AddDiagnostic(std::move(copy));
    }

    auto Diagnostics::AddDiagnostic(Diagnostic &&diagnostic) -> void {
        if (!diagnostic.filepath) {
            globalDiagnostics.push_back(std::move(diagnostic));
            return;
        }

        if (fileDiagnosticsLocks.find(*diagnostic.filepath) == fileDiagnosticsLocks.end()) {
            fileDiagnostics.insert(std::make_pair(*diagnostic.filepath, std::vector<Diagnostic>{}));
            fileDiagnosticsLocks.emplace(
                    std::piecewise_construct,
                    std::make_tuple(*diagnostic.filepath),
                    std::make_tuple()
            );
            return;
        }

        auto filepath = *diagnostic.filepath;

        fileDiagnosticsLocks[filepath].lock();
        fileDiagnostics[filepath].push_back(std::move(diagnostic));
        fileDiagnosticsLocks[filepath].unlock();
    }
}
