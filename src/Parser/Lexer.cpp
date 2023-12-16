#include <fstream>
#include "Parser/Lexer.h"

namespace virgo::parser {
    namespace {
        std::string ReadFile(const std::string &filepath) {
            std::ifstream file;
            file.exceptions(std::ifstream::failbit);
            file.open(filepath, std::ios::in);

            auto contents = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
            file.close();

            return contents;
        }
    }

    Lexer::Lexer(const std::string &filepath)
        : filepath(filepath) {
        this->codePoints = common::CodePointsIterator(ReadFile(filepath));
        this->current = this->codePoints.NextCodePoint();
    }

    Lexer::Lexer(const std::string &filepath, const std::string &source)
            : filepath(filepath), codePoints(source) {
        this->current = this->codePoints.NextCodePoint();
    }

    Lexer::Lexer(const std::string &filepath, std::string &&source)
            : filepath(filepath), codePoints(std::move(source)) {
        this->current = this->codePoints.NextCodePoint();
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
        while (!IsEof() && common::IsAsciiWhitespace(current.value())) {
            Advance();
        }
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

    auto Lexer::NextToken() -> ast::Token {
        SkipWhitespaces();

        if (IsEof()) {
            return {ast::TokenKind::EndOfFile,
                    common::Span::SingleByteSpan(cursor)};
        }

        auto _current = current.value();

        return {ast::TokenKind::Error,
                common::Span::SingleByteSpan(cursor)};
    }
}