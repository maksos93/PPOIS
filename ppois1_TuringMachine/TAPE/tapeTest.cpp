#include <gtest/gtest.h>
#include "tape.h"

TEST(TapeTest,EmptyTape){
    Tape t;
    EXPECT_EQ(t.Size(), 1u);
    EXPECT_EQ(t.GetHead(), 0u);
    EXPECT_EQ(t.Read(), '_');
    EXPECT_EQ(t.GetBlank(), '_');
};

TEST(TapeTest, ConstructFromString){
    Tape t("acb");
    EXPECT_EQ(t.Content(), "abc");
    EXPECT_EQ(t.Size(), 3u);
    EXPECT_EQ(t.Read(), 'a');
};

TEST(TapeTest, ReadWrite){
    Tape t("abc");
    EXPECT_EQ(t.Read(), 'a');
    t.Write('X');
    EXPECT_EQ(t.Read(), 'X');
    EXPECT_EQ(t.Content(), "Xbc");
};

TEST(TapeTest, MoveRight){
    Tape t("ab");
    t.MoveRight();
    EXPECT_EQ(t.GetHead(), 1u);
    EXPECT_EQ(t.Read(), 'a');
    t.MoveRight();
    EXPECT_EQ(t.GetHead(), 2u);
    EXPECT_EQ(t.Read(), '_');
    EXPECT_EQ(t.Size(), 3u);
};

TEST(TapeTest, MoveLeft){
    Tape t("ab");
    t.MoveLeft();
    EXPECT_EQ(t.GetHead(), 0u);
    EXPECT_EQ(t.Read(), '_');
    EXPECT_EQ(t.Content(), "_ab");
    t.MoveRight();
    EXPECT_EQ(t.Read(), 'a');
};

TEST(TapeTest, SetHead){
    Tape t("ab");
    t.SetHead(5);
    EXPECT_EQ(t.GetHead(), 5u);
    EXPECT_GE(t.Size(), 6u);
    EXPECT_EQ(t.Read(), '_');
};

TEST(TapeTest, Clear){
    Tape t("abcdef");
    t.Clear();
    EXPECT_EQ(t.Size(), 1u);
    EXPECT_EQ(t.GetHead(), 0u);
    EXPECT_EQ(t.Read(), '_');
};

TEST(TapeTest, CustomBlank){
    Tape t("ab", '.');
    EXPECT_EQ(t.GetBlank(), '.');
    t.MoveLeft();
    EXPECT_EQ(t.Read(), '.');
};

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};