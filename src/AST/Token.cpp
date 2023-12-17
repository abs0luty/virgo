#include "AST/Token.h"

namespace virgo::ast {
    namespace {
        bool RequiresStringToBeStored(TokenKind kind) {
            switch (kind) {
                case String:
                case Identifier:
                case Comment:
                case ItemComment:
                case ModuleComment:
                    return true;
                default:
                    return false;
            }
        }
    }

    Token::Token(const Token& token)
        : kind(token.kind), span(token.span) {
        if (RequiresStringToBeStored(this->kind)) {
            this->string = token.string;
        } else if (token.kind == Integer) {
            this->integer = token.integer;
        } else if (token.kind == Float) {
            this->float_ = token.float_;
        } else if (token.kind == Character) {
            this->character = token.character;
        } else if (token.kind == Boolean) {
            this->boolean = token.boolean;
        } else if (token.kind == Error) {
            this->error = token.error;
        }
    }

    Token::~Token() {
        if (RequiresStringToBeStored(this->kind)) {
            string.~basic_string();
        }
    }
}
