#include "gtest/gtest.h"
#include "Common/Encoding.h"

using namespace virgo::common;

TEST(UtilityTests, IsWhitespace) {
    EXPECT_TRUE(IsWhitespace(' '));
    EXPECT_TRUE(IsWhitespace('\t'));
    EXPECT_TRUE(IsWhitespace('\n'));
    EXPECT_TRUE(IsWhitespace('\r'));
    EXPECT_FALSE(IsWhitespace('a'));
    EXPECT_FALSE(IsWhitespace('\0'));
}

TEST(UtilityTests, XID) {
    EXPECT_TRUE(IsXIDStart('a'));
    EXPECT_TRUE(IsXIDContinue('a'));
    EXPECT_TRUE(IsXIDStart('A'));
    EXPECT_TRUE(IsXIDContinue('A'));
    EXPECT_FALSE(IsXIDStart('0'));
    EXPECT_TRUE(IsXIDContinue('0'));

    // TODO: Add support for Unicode Standard Anex #31.
    //    EXPECT_TRUE(IsXIDStart(U'\u044B')); // 'ы'

    EXPECT_TRUE(IsXIDStart('_'));
    EXPECT_TRUE(IsXIDContinue('_'));

    EXPECT_FALSE(IsXIDStart('\t'));
    EXPECT_FALSE(IsXIDContinue('\r'));
    EXPECT_FALSE(IsXIDStart('\n'));
    EXPECT_FALSE(IsXIDContinue(' '));
    EXPECT_FALSE(IsXIDStart('\0'));
}

TEST(UtilityTests, IterateOverAsciiString) {
    Utf8StringIterator it("test");
    EXPECT_EQ(it.NextCodePoint(), 't');
    EXPECT_EQ(it.NextCodePoint(), 'e');
    EXPECT_EQ(it.NextCodePoint(), 's');
    EXPECT_EQ(it.NextCodePoint(), 't');
    EXPECT_FALSE(it.NextCodePoint());
}

TEST(UtilityTests, IteratorOverUtf8String) {
    Utf8StringIterator it("тест");
    EXPECT_EQ(it.NextCodePoint(), 0x0442);
    EXPECT_EQ(it.NextCodePoint(), 0x0435);
    EXPECT_EQ(it.NextCodePoint(), 0x0441);
    EXPECT_EQ(it.NextCodePoint(), 0x0442);
    EXPECT_FALSE(it.NextCodePoint());
}
