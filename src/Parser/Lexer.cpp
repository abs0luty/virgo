#include "Parser/Lexer.h"

#include <fstream>

namespace virgo::parser {
    std::string ReadFile(const std::string &filepath) noexcept(false) {
        std::ifstream file;
        file.exceptions(std::ifstream::failbit);
        file.open(filepath, std::ios::in);

        auto contents = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        file.close();

        return contents;
    }

    Lexer::Lexer(const std::string &filepath)
        : filepath(filepath) {
        this->codePoints = common::CodePointsIterator(ReadFile(filepath));
        this->current = this->codePoints.NextCodePoint();
        this->next = this->codePoints.NextCodePoint();
    }

    Lexer::Lexer(const std::string &filepath, const std::string &source)
            : filepath(filepath), codePoints(source) {
        this->current = this->codePoints.NextCodePoint();
        this->next = this->codePoints.NextCodePoint();
    }

    Lexer::Lexer(const std::string &filepath, std::string &&source)
            : filepath(filepath), codePoints(std::move(source)) {
        this->current = this->codePoints.NextCodePoint();
        this->next = this->codePoints.NextCodePoint();
    }

    auto Lexer::IsEof() const noexcept -> bool {
        return this->current == std::nullopt;
    }

    auto Lexer::BytesInCurrentCodePoint() const noexcept(false) -> std::size_t {
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

    auto Lexer::Advance() noexcept -> void {
        if (this->current != std::nullopt) {
            this->cursor.offset += this->BytesInCurrentCodePoint();

            if (this->current == '\n') {
                this->cursor.line++;
                this->cursor.column = 0;
            } else {
                this->cursor.column++;
            }
        }

        this->current = this->next;
        this->next = this->codePoints.NextCodePoint();
    }
}