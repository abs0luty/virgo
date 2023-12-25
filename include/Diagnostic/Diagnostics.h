#ifndef VIRGO_DIAGNOSTICS_H
#define VIRGO_DIAGNOSTICS_H

#include <unordered_map>
#include <map>
#include <vector>
#include <mutex>
#include "Diagnostic/Diagnostic.h"
#include "Diagnostic/DiagnosticsEmitter.h"

namespace virgo::diagnostic {
    /*!
     * A class that manages diagnostics synchronization in computations
     * across threads like parallel parsing
     */
    class Diagnostics final {
    public:
        Diagnostics() {}

        /**
         * @brief   Copy and then add a diagnostic to the diagnostics list
         * @details Locks the mutex associated with the given file path
         *          or when no file path is given locks the global diagnostics
         *          mutex
         * @param   diagnostic Diagnostic to add
         */
        auto AddDiagnostic(const Diagnostic& diagnostic) -> void;

        /**
         * @brief   Add a diagnostic to the diagnostics list
         * @details Locks the mutex associated with the given file path
         *          or when no file path is given locks the global diagnostics
         *          mutex
         * @param   diagnostic Diagnostic to add
         */
        auto AddDiagnostic(Diagnostic &&diagnostic) -> void;

        ~Diagnostics() = default;

    private:
        /**
         * Diagnostics not associated with any file.
         */
        std::vector<Diagnostic> globalDiagnostics;

        /**
         * Lock for the global diagnostics data.
         */
        std::mutex globalDiagnosticsLock;

        /**
         * Map of file paths to diagnostics data.
         */
        std::map<std::string, std::vector<Diagnostic>> fileDiagnostics;

        /**
         * Map of file paths to locks for related diagnostics data.
         */
        std::unordered_map<std::string, std::mutex> fileDiagnosticsLocks;
    };
}

#endif //VIRGO_DIAGNOSTICS_H
