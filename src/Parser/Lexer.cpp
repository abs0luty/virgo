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

    auto Lexer::Advance() -> void {
        if (this->current != std::nullopt) {
            this->cursor.offset += this->BytesInCurrentCodePoint();

            if (this->current == '\n') {
                this->cursor.line++;
                this->cursor.column = 0;
            } else {
                this->cursor.column++;
            }
        }

        this->current = this->codePoints.NextCodePoint();
    }

    auto Lexer::NextToken() -> ast::Token {
        SkipWhitespaces();

        if (this->IsEof()) {
            return {ast::TokenKind::EndOfFile,
                    common::Span::SingleByteSpan(this->cursor)};
        }

        auto _current = this->current.value();

        return {ast::TokenKind::Error,
                common::Span::SingleByteSpan(this->cursor)};
    }
}