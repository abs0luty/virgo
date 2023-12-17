#include <fstream>
#include "Parser/Lexer.h"

namespace virgo::parser {
    using namespace virgo::ast;

    Lexer::Lexer(const std::string &filepath, const std::string &source)
            : filepath(filepath), codePoints(source) {
        this->current = this->codePoints.NextCodePoint();
        this->source = source;
    }

    Lexer::Lexer(const std::string &filepath, std::string &&source)
            : filepath(filepath), codePoints(source) {
        this->current = this->codePoints.NextCodePoint();
        this->source = std::move(source);
    }

    auto inline Lexer::IsEof() const -> bool {
        return current == std::nullopt;
    }

    auto inline Lexer::BytesInCurrentCodePoint() const -> std::size_t {
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
            common::Span::SingleByteSpan(cursor),
        };
        Advance();

        return token;
    }

    auto inline Lexer::CurrentByteToken(TokenKind kind) -> Token {
        return {
            kind,
            common::Span::SingleByteSpan(cursor),
        };
    }

    auto inline Lexer::NextIdentifierToken() -> Token {
        auto startLocation = cursor;

        while (common::IsXIDContinue(current)) {
            Advance();
        }

        return {Identifier,
                {startLocation, cursor},
                source.substr(startLocation.offset, cursor.offset)};
    }

    auto inline Lexer::NextCommentToken() -> Token {
        Advance(); // Skip the second `/`

        auto startLocation = cursor;

        while (!IsEof() && current != '\n') {
            Advance();
        }

        auto comment = source.substr(startLocation.offset, cursor.offset);

        if (comment.rfind('/', 0) == 0) {
            comment = comment.substr(1);

            return {
                ItemComment,
                {startLocation, cursor},
                comment
            };
        } else if (comment.rfind('!', 0) == 0) {
            comment = comment.substr(1);

            return {
                ModuleComment,
                {startLocation, cursor},
                comment
            };
        } else {
            return {
                Comment,
                {startLocation, cursor},
                comment
            };
        }
    }

#define SINGLE_CHAR_TOKEN(chr, kind) \
    else if (current == chr) { \
        return AdvanceWith(kind); \
    }
#define SINGLE_CHAR_TRIGER(chr, parse_fn) \
    else if (current == chr) { \
        return parse_fn(); \
    }

    auto Lexer::NextToken() -> Token {
        SkipWhitespaces();

        if (IsEof()) [[unlikely]]
            return CurrentByteToken(EndOfFile);

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
        SINGLE_CHAR_TOKEN(';', Semicolon)
        else if (current == '+') {
            Advance();

            if (current == '+')
                return AdvanceWith(DoublePlus);
            else if (current == '=')
                return AdvanceWith(PlusEq);
            else
                return CurrentByteToken(Plus);
        } else if (current == '-') {
            Advance();

            if (current == '-')
                return AdvanceWith(DoubleMinus);
            else if (current == '=')
                return AdvanceWith(MinusEq);
            else
                return CurrentByteToken(Minus);
        } else if (current == '*') {
            Advance();

            if (current == '*') {
                Advance();

                if (current == '=')
                    return AdvanceWith(DoubleAsteriskEq);
                else
                    return CurrentByteToken(DoubleAsterisk);
            } else if (current == '=')
                return AdvanceWith(AsteriskEq);
            else
                return CurrentByteToken(Asterisk);
        } else if (current == '/') {
            Advance();

            if (current == '/') {
                return NextCommentToken();
            } else
                return CurrentByteToken(Slash);
        }
        else if (current == '^') {
            Advance();

            if (current == '=')
                return AdvanceWith(CaretEq);
            else
                return CurrentByteToken(Caret);
        }

        if (common::IsXIDStart(current)) {
            return NextIdentifierToken();
        }

        return AdvanceWith(Error);
    }
}