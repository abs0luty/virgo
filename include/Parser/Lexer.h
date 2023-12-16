#ifndef VIRGO_LEXER_H
#define VIRGO_LEXER_H

#include <string>
#include <optional>
#include <utility>
#include "Common/CodePointsIterator.h"
#include "Common/Span.h"

namespace virgo::parser {
    class Lexer {
    public:
        std::string filepath;

        explicit Lexer(const std::string& filepath);
        Lexer(const std::string& filepath, const std::string& source);
        Lexer(const std::string& filepath, std::string&& source);
    private:
        common::ByteLocation cursor = common::ByteLocation::StartOfFile();
        common::CodePointsIterator codePoints;
        std::optional<char32_t> current, next;
        std::string stringBuffer;

        [[nodiscard]] auto IsEof() const noexcept -> bool;
        [[nodiscard]] auto BytesInCurrentCodePoint() const noexcept(false) -> std::size_t;

        auto Advance() noexcept -> void;
    };
}

#endif //VIRGO_LEXER_H
