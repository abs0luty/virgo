#include "AST/Token.h"

namespace virgo::ast {
    auto constexpr Token::ToString() const -> const char * {
        switch (this->kind) {
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
                return error.ToString();
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

    auto constexpr LexError::ToString() const -> const char * {
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
