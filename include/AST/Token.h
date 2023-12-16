#ifndef VIRGO_TOKEN_H
#define VIRGO_TOKEN_H

#include "Common/Span.h"
#include <string>

namespace virgo::ast {
    enum TokenKind {
        // Arrow (`->`).
        Arrow,
        // Single ampersand (`&`).
        Ampersand,
        // Ampersand equal (`&=`).
        AmpersandEq,
        // Double ampersand (`&&`).
        DoubleAmpersand,
        // Asterisk (`*`).
        Asterisk,
        // Double asterisk (`**`).
        DoubleAsterisk,
        // Asterisk equal (`*=`).
        AsteriskEq,
        // Double asterisk equal (`**=`).
        DoubleAsteriskEq,
        // At sign (`@`).
        At,
        // Bang (`!`).
        Bang,
        // Close brace (`}`).
        CloseBrace,
        // Close bracket (`]`).
        CloseBracket,
        // Close parenthesis (`)`).
        CloseParen,
        // Colon (`:`).
        Colon,
        // Comma (`,`).
        Comma,
        // Dot (`.`).
        Dot,
        // Double dot (`..`).
        DoubleDot,
        // Equal (`=`).
        Eq,
        // Double equal (`==`).
        DoubleEq,
        // Greater than (`>`).
        Greater,
        // Greater than or equal (`>=`).
        GreaterEq,
        // Left shift (`<<`).
        LeftShift,
        // Less than (`<`).
        Less,
        // Less than or equal (`<=`).
        LessEq,
        // Minus (`-`).
        Minus,
        // Minus equal (`-=`).
        MinusEq,
        // Double minus (`--`).
        DoubleMinus,
        // Tilde (`~`).
        Tilde,
        // Bang equal (`!=`).
        BangEq,
        // Open brace (`{`).
        OpenBrace,
        // Open bracket (`[`).
        OpenBracket,
        // Open parenthesis (`(`).
        OpenParen,
        // Or (`|`).
        Or,
        // Or equal (`|=`).
        OrEq,
        // Double or (`||`).
        DoubleOr,
        // Percent (`%`).
        Percent,
        // Percent equal (`%=`).
        PercentEq,
        // Plus (`+`).
        Plus,
        // Plus equal (`+=`).
        PlusEq,
        // Double plus (`++`).
        DoublePlus,
        // Question mark (`?`).
        Question,
        // Right shift (`>>`).
        RightShift,
        // Semicolon (`;`).
        Semicolon,
        // Slash (`/`).
        Slash,
        // Slash equal (`/=`).
        SlashEq,
        // Caret (`^`).
        Caret,
        // Caret equal (`^=`).
        CaretEq,
        // Hash (`#`).
        Hash,
        // Underscore (`_`).
        Underscore,
        // Keyword `as`.
        As,
        // Keyword `defer`.
        Defer,
        // Keyword `else`.
        Else,
        // Keyword `enum`.
        Enum,
        // Keyword `for`.
        For,
        // Keyword `fun`.
        Fun,
        // Keyword `if`.
        If,
        // Keyword `pub`.
        Pub,
        // Keyword `return`.
        Return,
        // Keyword `struct`.
        Struct,
        // Keyword `type`.
        Type,
        // Keyword `let`.
        Let,
        // Keyword `where`.
        Where,
        // Keyword `while`.
        While,
        // Keyword `match`.
        Match,
        // Keyword `import`.
        Import,
        // Keyword `break`.
        Break,
        // Keyword `continue`.
        Continue,
        // Keyword `dyn`.
        Dyn,
        // Keyword `loop`.
        Loop,
        // Keyword `interface`.
        Interface,
        // Keyword `implements`.
        Implements,
        // Boolean literal (`true` or `false`).
        Boolean,
        // Character literal,
        Character,
        // Corresponds to any comment that is not a doc comment.
        Comment,
        // Module level doc comment.
        ModuleComment,
        // Item level doc comment.
        ItemComment,
        // Identifier.
        Identifier,
        // Integer literal.
        Integer,
        // Floating point literal.
        Float,
        // String literal.
        String,
        // End of file.
        EndOfFile,
        // Error.
        Error,
    };

    struct LexError final {
        enum Value {
            DigitDoesNotCorrespondToBase,
            EmptyCharacterLiteral,
            EmptyEscapeSequence,
            EmptyWrappedIdentifier,
            ExpectedCloseBracketInByteEscapeSequence,
            ExpectedCloseBracketInUnicodeEscapeSequence,
            ExpectedDigitInUnicodeEscapeSequence,
            ExpectedDigitInByteEscapeSequence,
            ExpectedOpenBracketInUnicodeEscapeSequence,
            ExpectedOpenBracketInByteEscapeSequence,
            NoDigitsInExponent,
            NoDecimalMantissaInExponent,
            NoDigitsInNumber,
            InvalidByteEscapeSequence,
            InvalidDigit,
            InvalidRadixPoint,
            InvalidUnicodeEscapeSequence,
            MoreThanOneCharacterInCharacterLiteral,
            UnderscoreMustSeparateSuccessiveDigits,
            UnexpectedCharacter,
            UnknownEscapeSequence,
            UnterminatedCharacterLiteral,
            UnterminatedStringLiteral,
            UnterminatedWrappedIdentifier,
        };

        [[nodiscard]] auto constexpr ToString() const -> const char*;
    private:
        Value value;
    };

    class Token final {
        TokenKind kind;
        common::Span span;
        union {
            std::string string;
            std::int64_t integer{};
            double float_;
            char32_t character;
            bool boolean;
            LexError error;
        };

        Token(TokenKind kind, common::Span span)
            : kind(kind), span(span) {}
        Token(TokenKind kind, common::Span span, const std::string& string)
            : kind(kind), span(span), string(string) {}
        Token(TokenKind kind, common::Span span, std::string&& string)
            : kind(kind), span(span), string(std::move(string)) {}
        Token(common::Span span, int64_t integer)
            : kind(TokenKind::Integer), span(span), integer(integer) {}
        Token(common::Span span, double float_)
            : kind(TokenKind::Float), span(span), float_(float_) {}
        Token(common::Span span, char32_t character)
            : kind(TokenKind::Character), span(span), character(character) {}
        Token(common::Span span, bool boolean)
            : kind(TokenKind::Boolean), span(span), boolean(boolean) {}
        Token(common::Span span, LexError error)
            : kind(TokenKind::Error), span(span), error(error) {}

        [[nodiscard]] auto constexpr ToString() const -> const char*;
    };
}

#endif //VIRGO_TOKEN_H
