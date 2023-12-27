#ifndef VIRGO_IO_H
#define VIRGO_IO_H

#include <string>
#include <optional>
#include "Common/Error.h"

namespace virgo::common {
    /*!
     * Error, that occurs when a file could not be read
     */
    class FailedToReadFileError final: public Error {
    public:
        explicit FailedToReadFileError(std::string_view filepath)
        : Error("Cannot read the file", filepath) {}
    };

    /**
     * @brief  Reads a file contents into a string
     * @param  filepath Path to the file
     * @throws FailedToReadFileError if the file could not be read
     * @return The contents of the file
     */
    std::string ReadFile(std::string_view filepath);
}

#endif //VIRGO_IO_H
