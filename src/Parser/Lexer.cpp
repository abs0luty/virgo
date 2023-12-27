#include <fstream>
#include <cassert>
#include "Parser/Lexer.h"

namespace virgo::parser {
    using namespace virgo::ast;

    Lexer::Lexer(std::string_view filepath, std::string_view source,
                 diagnostic::Diagnostics& diagnostics)
            : filepath(filepath), source(source), codePoints(source),
              diagnostics(diagnostics) {
        current = codePoints.NextCodePoint();
    }

    auto inline Lexer::IsEof() const -> bool {
        return current == std::nullopt;
    }

    auto inline Lexer::BytesInCurrentCodePoint() const -> std::size_t {
        assert(current);

        auto codepoint = *current;

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

    auto inline Lexer::SkipWhitespaces() -> void {
        while (common::IsWhitespace(current))
            Advance();
    }

    auto Lexer::Advance() -> void {
        if (current != std::nullopt) {
            cursor.offset += BytesInCurrentCodePoint();

            if (current == '\n') {
                cursor.line++;
                cursor.column = 0;
            } else {
                cursor.column++;
            }
        }

        current = codePoints.NextCodePoint();
    }

    auto inline Lexer::AdvanceTwice() -> void {
        Advance();
        Advance();
    }

    auto inline Lexer::AdvanceWith(TokenKind kind) -> Token {
        Token token {
            kind,
            common::Span::OfSingleByte(cursor),
        };
        Advance();

        return token;
    }

    auto inline Lexer::AdvanceWithPreviousByte(virgo::ast::TokenKind kind) -> Token {
        Token token{
                kind,
                common::Span::OfTwoSuccessiveBytes(cursor.OfPreviousByte()),
        };
        Advance();

        return token;
    }

    auto inline Lexer::AdvanceWithSecondPreviousByte(ast::TokenKind kind) -> ast::Token {
        Token token{
                kind,
                common::Span::OfMultipleSuccessiveBytes(cursor.OfPreviousSecondByte(), 3),
        };
        Advance();

        return token;
    }

    auto inline Lexer::CurrentByteToken(TokenKind kind) -> Token {
        return {
                kind,
                common::Span::OfSingleByte(cursor)
        };
    }

    auto inline Lexer::PreviousByteToken(TokenKind kind) -> Token {
        return {
                kind,
                common::Span::OfSingleByte(cursor.OfPreviousByte()),
        };
    }

    auto inline Lexer::NextIdentifierToken() -> Token {
        auto startLocation = cursor;

        while (common::IsXIDContinue(current)) {
            Advance();
        }

        return {TokenKind::Identifier,
                {startLocation, cursor},
                std::string(source.substr(startLocation.offset, cursor.offset))};
    }

    // TODO: Implement
    auto inline Lexer::NextStringToken() -> Token { throw std::runtime_error("Not implemented"); }

    // TODO: Implement
    auto inline Lexer::NextCharacterToken() -> Token { throw std::runtime_error("Not implemented"); }

    auto inline Lexer::NextCommentToken() -> Token {
        Advance(); // Skip the second `/`

        auto startLocation = cursor;

        while (!IsEof() && current != '\n') {
            Advance();
        }

        auto comment = std::string(source.substr(startLocation.offset, cursor.offset));

        if (comment.rfind('/', 0) == 0) {
            comment = comment.substr(1);

            return {
                TokenKind::ItemComment,
                {startLocation, cursor},
                comment
            };
        } else if (comment.rfind('!', 0) == 0) {
            comment = comment.substr(1);

            return {
                TokenKind::ModuleComment,
                {startLocation, cursor},
                comment
            };
        } else {
            return {
                TokenKind::Comment,
                {startLocation, cursor},
                comment
            };
        }
    }

#define SINGLE_CHAR_TOKEN(chr, kind) \
    else if (current == chr) { \
        return AdvanceWith(TokenKind::kind); \
    }
#define SINGLE_CHAR_TRIGER(chr, parse_fn) \
    else if (current == chr) { \
        return parse_fn(); \
    }

    auto Lexer::NextToken() -> Token {
        SkipWhitespaces();

        if (IsEof()) [[unlikely]]
            return CurrentByteToken(TokenKind::EndOfFile);

        SINGLE_CHAR_TOKEN(':', Colon)
        SINGLE_CHAR_TOKEN('@', At)
        SINGLE_CHAR_TRIGER('"', NextStringToken)
        SINGLE_CHAR_TRIGER('\'', NextCharacterToken)
        SINGLE_CHAR_TOKEN('#', Hash)
        SINGLE_CHAR_TOKEN('(', OpenParen)
        SINGLE_CHAR_TOKEN(')', CloseParen)
        SINGLE_CHAR_TOKEN('{', OpenBrace)
        SINGLE_CHAR_TOKEN('}', CloseBrace)
        SINGLE_CHAR_TOKEN('[', OpenBracket)
        SINGLE_CHAR_TOKEN(']', CloseBracket)
        SINGLE_CHAR_TOKEN('~', Tilde)
        SINGLE_CHAR_TOKEN(',', Comma)
        SINGLE_CHAR_TOKEN('.', Dot)
        SINGLE_CHAR_TOKEN(';', Semicolon)
        else if (current == '+') {
            Advance();

            if (current == '+')
                return AdvanceWithPreviousByte(TokenKind::DoublePlus);
            else if (current == '=')
                return AdvanceWithPreviousByte(TokenKind::PlusEq);
            else
                return PreviousByteToken(TokenKind::Plus);
        } else if (current == '-') {
            Advance();

            if (current == '-')
                return AdvanceWithPreviousByte(TokenKind::DoubleMinus);
            else if (current == '=')
                return AdvanceWithPreviousByte(TokenKind::MinusEq);
            else
                return PreviousByteToken(TokenKind::Minus);
        } else if (current == '*') {
            Advance();

            if (current == '*') {
                Advance();

                if (current == '=')
                    return AdvanceWithSecondPreviousByte(TokenKind::DoubleAsteriskEq);
                else
                    return AdvanceWithPreviousByte(TokenKind::DoubleAsterisk);
            } else if (current == '=')
                return AdvanceWithPreviousByte(TokenKind::AsteriskEq);
            else
                return PreviousByteToken(TokenKind::Asterisk);
        } else if (current == '/') {
            Advance();

            if (current == '/') {
                return NextCommentToken();
            } else
                return PreviousByteToken(TokenKind::Slash);
        }
        else if (current == '^') {
            Advance();

            if (current == '=')
                return AdvanceWithPreviousByte(TokenKind::CaretEq);
            else
                return PreviousByteToken(TokenKind::Caret);
        }
        else if (common::IsXIDStart(current)) {
            return NextIdentifierToken();
        }

        return AdvanceWith(TokenKind::Error);
    }
}