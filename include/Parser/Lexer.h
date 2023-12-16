#ifndef VIRGO_LEXER_H
#define VIRGO_LEXER_H

#include <string>
#include <optional>
#include <utility>
#include "AST/Token.h"
#include "Common/Encoding.h"
#include "Common/CodePointsIterator.h"
#include "Common/Span.h"

namespace virgo::parser {
    class Lexer final {
    public:
        // Path to the file being processed.
        std::string filepath;

        explicit Lexer(const std::string& filepath);
        Lexer(const std::string& filepath, const std::string& source);
        Lexer(const std::string& filepath, std::string&& source);

        // Returns the next token and updates the state of the lexer's
        // state machine (moves to the next Unicode code point).
        auto NextToken() -> ast::Token;
    private:
        // Location of the currently processed byte.
        common::ByteLocation cursor = common::ByteLocation::StartOfFile();

        // Iterator over Unicode code points in UTF8 file contents.
        common::CodePointsIterator codePoints;

        // Current Unicode code point.
        std::optional<char32_t> current;

        // Returns true if the end of the file has been reached.
        [[nodiscard]] auto inline IsEof() const -> bool {
            return this->current == std::nullopt;
        }

        // Returns the number of bytes in the current code point.
        [[nodiscard]] auto inline BytesInCurrentCodePoint() const -> std::size_t {
            auto codepoint = this->current.value();

            if (codepoint < 0x80) {
                return 1;
            } else if (codepoint < 0x800) {
                return 2;
            } else if (codepoint < 0x10000) {
                return 3;
            } else {
                return 4;
            }
        }

        // Skip through whitespaces.
        auto inline SkipWhitespaces() -> void {
            while (!this->IsEof() && common::IsAsciiWhitespace(this->current.value())) {
                this->Advance();
            }
        }

        // Advance lexer's state to the next Unicode code point.
        auto Advance() -> void;
    };
}

#endif //VIRGO_LEXER_H
