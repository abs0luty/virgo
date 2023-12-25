#include "gtest/gtest.h"
#include "Parser/Lexer.h"

using namespace virgo::parser;
using namespace virgo::ast;
using namespace virgo::common;

#define START_LEXER_TEST(source) \
    Lexer lexer("test", source); \
    Token token;
    ByteLocation start_, end_;

#define CHECK_NEXT_TOKEN(kind_v, start_v, end_v) \
    token = lexer.NextToken(); \
    EXPECT_EQ(token.kind, kind_v);               \
    EXPECT_EQ(token.span.start, ByteLocation start_v); \
    EXPECT_EQ(token.span.end, ByteLocation end_v);

TEST(LexerTests, EndOfFile) {
    START_LEXER_TEST("")
    CHECK_NEXT_TOKEN(TokenKind::EndOfFile, ({1, 0, 0}), ({1, 1, 1}))
    CHECK_NEXT_TOKEN(TokenKind::EndOfFile, ({1, 0, 0}), ({1, 1, 1}))
}

TEST(LexerTests, EndOfFile2) {
    START_LEXER_TEST("\n\r\t ")
    CHECK_NEXT_TOKEN(TokenKind::EndOfFile, ({2, 3, 4}), ({2, 4, 5}))
}

TEST(LexerTests, Identifier) {
    START_LEXER_TEST("_testBa9380f_")
    CHECK_NEXT_TOKEN(TokenKind::Identifier, ({1, 0, 0}), ({1, 13, 13}))
    CHECK_NEXT_TOKEN(TokenKind::EndOfFile, ({1, 13, 13}), ({1, 14, 14}))
}

TEST(LexerTests, Punctuation) {
    START_LEXER_TEST("()[]{},.")
    CHECK_NEXT_TOKEN(TokenKind::OpenParen, ({1, 0, 0}), ({1, 1, 1}))
    CHECK_NEXT_TOKEN(TokenKind::CloseParen, ({1, 1, 1}), ({1, 2, 2}))
    CHECK_NEXT_TOKEN(TokenKind::OpenBracket, ({1, 2, 2}), ({1, 3, 3}))
    CHECK_NEXT_TOKEN(TokenKind::CloseBracket, ({1, 3, 3}), ({1, 4, 4}))
    CHECK_NEXT_TOKEN(TokenKind::OpenBrace, ({1, 4, 4}), ({1, 5, 5}))
    CHECK_NEXT_TOKEN(TokenKind::CloseBrace, ({1, 5, 5}), ({1, 6, 6}))
    CHECK_NEXT_TOKEN(TokenKind::Comma, ({1, 6, 6}), ({1, 7, 7}))
    CHECK_NEXT_TOKEN(TokenKind::Dot, ({1, 7, 7}), ({1, 8, 8}))
    CHECK_NEXT_TOKEN(TokenKind::EndOfFile, ({1, 8, 8}), ({1, 9, 9}))
}

TEST(LexerTests, SingleByteOperator) {
    START_LEXER_TEST("+")
    CHECK_NEXT_TOKEN(TokenKind::Plus, ({1, 0, 0}), ({1, 1, 1}))
}

TEST(LexerTests, TwoBytesOperator) {
    START_LEXER_TEST("++")
    CHECK_NEXT_TOKEN(TokenKind::DoublePlus, ({1, 0, 0}), ({1, 2, 2}))
}

TEST(LexerTests, ThreeBytesOperator) {
    START_LEXER_TEST("**=")
    CHECK_NEXT_TOKEN(TokenKind::DoubleAsteriskEq, ({1, 0, 0}), ({1, 3, 3}))
}
