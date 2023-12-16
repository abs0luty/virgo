#include "AST/Token.h"

namespace virgo::ast {
    Token::~Token() {
        if (kind == String
            || kind == Identifier
            || kind == Comment
            || kind == ItemComment
            || kind == ModuleComment) {
            string.~basic_string();
        }
    }
}
