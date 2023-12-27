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
        Diagnostics() = default;

        /**
         * @brief   Construct a diagnostic struct from given arguments,
         *          and add it to the diagnostics list
         * @details Locks the mutex associated with the given file path
         *          or when no file path is given locks the global diagnostics
         *          mutex
         * @param   args Arguments used to construct the diagnostic struct
         * @tparam  Args Type of arguments used to construct the diagnostic struct
         */
        template <class ...Args,
                  class = std::enable_if_t<std::is_constructible_v<Diagnostic, Args...>>>
        auto AddDiagnostic(Args&&... args) -> void {
            AddDiagnosticImpl(Diagnostic(std::forward<Args>(args)...));
        }

        ~Diagnostics() = default;

    private:
        /**
         * Diagnostics not associated with any file
         */
        std::vector<Diagnostic> globalDiagnostics;

        /**
         * Lock for the global diagnostics data
         */
        std::mutex globalDiagnosticsLock;

        /**
         * Map of file paths to diagnostics data
         */
        std::map<std::string_view, std::vector<Diagnostic>> fileDiagnostics;

        /**
         * Map of file paths to locks for related diagnostics data
         */
        std::unordered_map<std::string_view, std::mutex> fileDiagnosticsLocks;

        auto AddDiagnosticImpl(Diagnostic&& diagnostics) -> void;
    };
}

#endif //VIRGO_DIAGNOSTICS_H
