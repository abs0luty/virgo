#include "AST/Token.h"

namespace virgo::ast {
    auto PrintTo(const TokenKind& kind, std::ostream* os) -> void {
        *os << kind.ToString();
    }

    auto PrintTo(const Token& token, std::ostream* os) -> void {
        *os << "Token(kind: " << token.kind.ToString() << ", span: ";
        PrintTo(token.span, os);
        if (token.kind.RequiresStringToBeStored()) {
            *os << ", string: " << token.string;
        } else if (token.kind == TokenKind::Integer) {
            *os << ", integer: " << token.integer;
        } else if (token.kind == TokenKind::Float) {
            *os << ", float: " << token.float_;
        } else if (token.kind == TokenKind::Character) {
            *os << ", character: " << (int) token.character;
        } else if (token.kind == TokenKind::Boolean) {
            *os << ", boolean: " << token.boolean;
        } else if (token.kind == TokenKind::Error) {
            *os << ", error: " << token.error.ToString();
        }
        *os << ")";
    }

    Token::Token(const Token& token)
        : kind(token.kind), span(token.span) {
        if (kind.RequiresStringToBeStored()) {
            this->string = token.string;
        } else if (token.kind == TokenKind::Integer) {
            this->integer = token.integer;
        } else if (token.kind == TokenKind::Float) {
            this->float_ = token.float_;
        } else if (token.kind == TokenKind::Character) {
            this->character = token.character;
        } else if (token.kind == TokenKind::Boolean) {
            this->boolean = token.boolean;
        } else if (token.kind == TokenKind::Error) {
            this->error = token.error;
        }
    }

    Token::~Token() {
        if (kind.RequiresStringToBeStored()) {
            string.~basic_string();
        }
    }
}
