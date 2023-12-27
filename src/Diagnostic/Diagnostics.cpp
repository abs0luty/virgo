#include "Diagnostic/Diagnostics.h"

namespace virgo::diagnostic {
    auto Diagnostics::AddDiagnosticImpl(Diagnostic&& diagnostic) -> void {
        if (!diagnostic.filepath) {
            const std::lock_guard<std::mutex> lock(globalDiagnosticsLock);
            globalDiagnostics.push_back(diagnostic);
            return;
        }

        const auto filepath = *diagnostic.filepath;

        if (fileDiagnosticsLocks.find(filepath) == fileDiagnosticsLocks.end()) {
            fileDiagnostics.insert(std::make_pair(
                    filepath,
                    std::vector<Diagnostic>{diagnostic}));
            fileDiagnosticsLocks.emplace(
                    std::piecewise_construct,
                    std::make_tuple(filepath),
                    std::make_tuple()
            );
            return;
        }

        const std::lock_guard<std::mutex> lock(fileDiagnosticsLocks[filepath]);
        fileDiagnostics[filepath].push_back(diagnostic);
    }
}
