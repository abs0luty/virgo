#ifndef VIRGO_TOKEN_H
#define VIRGO_TOKEN_H

#include <string>
#include "Common/Span.h"

namespace virgo::ast {
    class TokenKind final {
    public:
        enum Value {
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

        constexpr TokenKind() = default;

        /* implicit */ constexpr TokenKind(Value value) : value(value) {}

        constexpr operator Value() const {
            return value;
        }

        [[nodiscard]] constexpr auto ToString() const -> const char*;

        [[nodiscard]] constexpr auto RequiresStringToBeStored() const -> bool {
            switch (value) {
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

    private:
        Value value;
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

        constexpr auto operator==(const LexError& other) const -> bool {
            return value == other.value;
        };

        [[nodiscard]] constexpr auto ToString() const -> const char*;

    private:
        Value value;
    };

    class Token final {
    public:
        TokenKind kind{};
        common::Span span{};
        union {
            std::string string{};
            std::int64_t integer;
            double float_;
            char32_t character;
            bool boolean;
            LexError error;
        };

        Token() {}
        Token(const Token& token);

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

        auto operator=(const Token& token) -> void {
          kind = token.kind;
          span = token.span;
          string = token.string;
          integer = token.integer;
          float_ = token.float_;
          character = token.character;
          boolean = token.boolean;
          error = token.error;
        }

        constexpr auto operator==(const Token& token) const -> bool {
            if (kind != token.kind)
                return false;

            if (kind.RequiresStringToBeStored())
                return string == token.string;
            else if (token.kind == TokenKind::Integer)
                return integer == token.integer;
            else if (token.kind == TokenKind::Float)
                return float_ == token.float_;
            else if (token.kind == TokenKind::Character)
                return character == token.character;
            else if (token.kind == TokenKind::Boolean)
                return boolean == token.boolean;
            else if (token.kind == TokenKind::Error)
                return error == token.error;

            return true;
        }

        ~Token();
    };

    auto PrintTo(const TokenKind& kind, std::ostream* os) -> void;
    auto PrintTo(const Token& token, std::ostream* os) -> void;

    constexpr auto TokenKind::ToString() const -> const char * {
        switch (this->value) {
            case Identifier:
                return "identifier";
            case Integer:
                return "integer";
            case Float:
                return "float";
            case Character:
                return "character";
            case Boolean:
                return "boolean";
            case String:
                return "string";
            case Error:
                return "error token";
            case EndOfFile:
                return "end of file";
            case Arrow:
                return "`->`";
            case Colon:
                return "`:`";
            case Comma:
                return "``,`";
            case Dot:
                return "`.`";
            case OpenBracket:
                return "`[`";
            case CloseBracket:
                return "`]`";
            case OpenParen:
                return "`(`";
            case CloseParen:
                return "`)`";
            case OpenBrace:
                return "`{`";
            case CloseBrace:
                return "`}`";
            case Plus:
                return "`+`";
            case Minus:
                return "`-`";
            case Asterisk:
                return "`*`";
            case Slash:
                return "`/`";
            case Percent:
                return "`%`";
            case Eq:
                return "`=`";
            case Bang:
                return "`!`";
            case Less:
                return "`<`";
            case Greater:
                return "`>`";
            case LessEq:
                return "`<=`";
            case GreaterEq:
                return "`>=`";
            case DoubleEq:
                return "`==`";
            case BangEq:
                return "`!=`";
            case Ampersand:
                return "`&`";
            case DoubleAmpersand:
                return "`&&`";
            case AmpersandEq:
                return "`&=`";
            case Tilde:
                return "`~`";
            case At:
                return "`@`";
            case LeftShift:
                return "`<<`";
            case RightShift:
                return "`>>`";
            case DoubleDot:
                return "`..`";
            case DoubleMinus:
                return "`--`";
            case DoublePlus:
                return "`++`";
            case DoubleAsterisk:
                return "`**`";
            case DoubleAsteriskEq:
                return "`**=`";
            case Question:
                return "`?`";
            case Semicolon:
                return "`;`";
            case Hash:
                return "`#`";
            case Caret:
                return "`^`";
            case CaretEq:
                return "`^=`";
            case Or:
                return "`|`";
            case OrEq:
                return "`|=`";
            case DoubleOr:
                return "`||`";
            case PercentEq:
                return "`%=`";
            case PlusEq:
                return "`+=`";
            case MinusEq:
                return "`-=`";
            case AsteriskEq:
                return "`*=`";
            case SlashEq:
                return "`/=`";
            case Underscore:
                return "`_`";
            case As:
                return "`as`";
            case Break:
                return "`break`";
            case Defer:
                return "`defer`";
            case Else:
                return "`else`";
            case If:
                return "`if`";
            case Let:
                return "`let`";
            case Loop:
                return "`loop`";
            case Return:
                return "`return`";
            case While:
                return "`while`";
            case Where:
                return "`where`";
            case Pub:
                return "`pub`";
            case Struct:
                return "`struct`";
            case Type:
                return "`type`";
            case Fun:
                return "`fun`";
            case Import:
                return "`import`";
            case Enum:
                return "`enum`";
            case For:
                return "`for`";
            case Match:
                return "`match`";
            case Continue:
                return "`continue`";
            case Dyn:
                return "`dyn`";
            case Interface:
                return "`interface`";
            case Implements:
                return "`implements`";
            case Comment:
                return "comment";
            case ModuleComment:
                return "module doc comment";
            case ItemComment:
                return "doc comment";
        }
    }

    constexpr auto LexError::ToString() const -> const char * {
        switch (this->value) {
            case DigitDoesNotCorrespondToBase:
                return "digit doesn't correspond to the base";
            case EmptyCharacterLiteral:
                return "empty character literal";
            case EmptyEscapeSequence:
                return "empty escape sequence";
            case EmptyWrappedIdentifier:
                return "empty wrapped identifier";
            case ExpectedCloseBracketInByteEscapeSequence:
                return "expected close bracket (`}`) in byte escape sequence";
            case ExpectedCloseBracketInUnicodeEscapeSequence:
                return "expected close bracket (`}`) in Unicode escape sequence";
            case ExpectedDigitInUnicodeEscapeSequence:
                return "expected digit in Unicode escape sequence";
            case ExpectedDigitInByteEscapeSequence:
                return "expected digit in byte escape sequence";
            case ExpectedOpenBracketInUnicodeEscapeSequence:
                return "expected open bracket (`{`) in Unicode escape sequence";
            case ExpectedOpenBracketInByteEscapeSequence:
                return "expected open bracket (`{`) in byte escape sequence";
            case NoDigitsInExponent:
                return "no digits found in exponent";
            case NoDecimalMantissaInExponent:
                return "no decimal mantissa found in exponent";
            case NoDigitsInNumber:
                return "no digits found in number";
            case InvalidByteEscapeSequence:
                return "invalid byte escape sequence";
            case InvalidDigit:
                return "invalid digit";
            case InvalidRadixPoint:
                return "invalid radix point";
            case InvalidUnicodeEscapeSequence:
                return "invalid Unicode escape sequence";
            case MoreThanOneCharacterInCharacterLiteral:
                return "more than one character in character literal";
            case UnderscoreMustSeparateSuccessiveDigits:
                return "underscore must separate successive digits";
            case UnexpectedCharacter:
                return "unexpected character";
            case UnknownEscapeSequence:
                return "unknown escape sequence";
            case UnterminatedCharacterLiteral:
                return "unterminated character literal";
            case UnterminatedStringLiteral:
                return "unterminated string literal";
            case UnterminatedWrappedIdentifier:
                return "unterminated wrapped identifier";
        }
    }
}

#endif //VIRGO_TOKEN_H
