#ifndef VIRGO_LEXER_H
#define VIRGO_LEXER_H

#include <string>
#include <optional>
#include <utility>
#include "AST/Token.h"
#include "Common/Encoding.h"
#include "Common/Span.h"
#include "Diagnostic/Diagnostics.h"

namespace virgo::parser {
    /*!
     * A state machine for tokenizing a source file.
     *
     * @see NextToken
     */
    class Lexer final {
    public:
        /**
         * Path to the source file being currently processed
         */
        std::string_view filepath;

        /**
         * Source file contents
         */
        std::string_view source;

        Lexer(std::string_view filepath, std::string_view source,
              diagnostic::Diagnostics& diagnostics);

        /**
         * @brief  Returns the next token and updates the state of the lexer's
         *         state machine (moves to the next Unicode code point)
         * @return the next token
         */
        auto NextToken() -> ast::Token;

    private:
        /**
         * Location of the currently processed byte
         */
        common::ByteLocation cursor = common::ByteLocation::StartOfFile();

        /**
         * Iterator over Unicode code points in UTF8 file contents
         */
        common::Utf8StringIterator codePoints;

        /**
         * Current Unicode code point
         */
        std::optional<char32_t> current;

        /**
         * Global diagnostics storage
         */
        diagnostic::Diagnostics& diagnostics;

        /**
         * @return true if the end of the file has been reached
         *         false otherwise
         */
        [[nodiscard]] auto inline IsEof() const -> bool;

        /**
         * @return the number of bytes in the current code point
         */
        [[nodiscard]] auto inline BytesInCurrentCodePoint() const -> std::size_t;

        auto inline SkipWhitespaces() -> void;

        auto inline NextIdentifierToken() -> ast::Token;
        auto inline NextStringToken() -> ast::Token;
        auto inline NextCharacterToken() -> ast::Token;
        auto inline NextCommentToken() -> ast::Token;

        /**
         * @brief Advances the lexer state to the next Unicode code point
         */
        auto Advance() -> void;

        /**
         * @brief Advances the lexer state to the next Unicode code point twice
         * @see   Advance
         */
        auto inline AdvanceTwice() -> void;

        /**
         * @brief  Advances the lexer state to the next Unicode code point and
         *         returns the token with location being the current code point
         *         location in the source text
         * @return the token
         * @see    Advance
         */
        auto inline AdvanceWith(ast::TokenKind) -> ast::Token;

        auto inline AdvanceWithPreviousByte(ast::TokenKind kind) -> ast::Token;
        auto inline AdvanceWithSecondPreviousByte(ast::TokenKind kind) -> ast::Token;

        auto inline CurrentByteToken(ast::TokenKind) -> ast::Token;
        auto inline PreviousByteToken(ast::TokenKind) -> ast::Token;
    };
}

#endif //VIRGO_LEXER_H
