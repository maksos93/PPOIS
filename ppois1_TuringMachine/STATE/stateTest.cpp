#include "state.h"
#include <gtest/gtest.h>

TEST(stateTest, NameAndTransitions){
    State s("S");
    EXPECT_EQ(s.GetName(), "S");
    EXPECT_FALSE(s.HasTransition('a'));

    s.AddTransition('a', 'b', 'L', "T");
    EXPECT_TRUE(s.HasTransition('a'));
    EXPECT_TRUE(s.GetWrite('a').has_value());
    EXPECT_EQ(*s.GetWrite('a'), 'b');
    EXPECT_TRUE(s.GetMove('a').has_value());
    EXPECT_EQ(*s.GetMove('a'), 'L');
    EXPECT_TRUE(s.GetNext('a').has_value());
    EXPECT_EQ(*s.GetNext('a'), "T");
    EXPECT_FALSE(s.HasTransition('c'));
};

TEST(stateTest, MultipleTransitions){
    State s("X");
    s.AddTransition('0', '1', 'R', "X");
    s.AddTransition('1', '0', 'L', "Y");

    EXPECT_TRUE(s.HasTransition('0'));
    EXPECT_TRUE(s.HasTransition('1'));
    EXPECT_TRUE(s.GetWrite('0').has_value());
    EXPECT_EQ(*s.GetWrite('0'), '1');
    EXPECT_TRUE(s.GetNext('0').has_value());
    EXPECT_EQ(*s.GetNext('0'), "X");
    EXPECT_TRUE(s.GetWrite('1').has_value());
    EXPECT_EQ(*s.GetWrite('1'), '0');
    EXPECT_TRUE(s.GetNext('1').has_value());
    EXPECT_EQ(*s.GetNext('1'), "Y");
};

TEST(stateTest, ReplaceTransition){
    State s("S");
    s.AddTransition('x', 'y', 'R', "Z");

    EXPECT_TRUE(s.GetWrite('x').has_value());
    EXPECT_EQ(*s.GetWrite('x'), 'y');
    EXPECT_TRUE(s.GetMove('x').has_value());
    EXPECT_EQ(*s.GetMove('x'), 'R');
    EXPECT_TRUE(s.GetNext('x').has_value());
    EXPECT_EQ(*s.GetNext('x'), "X");

    s.AddTransition('x', 'z', 'L', "W");

    EXPECT_TRUE(s.GetWrite('x').has_value());
    EXPECT_EQ(*s.GetWrite('x'), 'z');
    EXPECT_TRUE(s.GetMove('x').has_value());
    EXPECT_EQ(*s.GetMove('x'), 'L');
    EXPECT_TRUE(s.GetNext('x').has_value());
    EXPECT_EQ(*s.GetNext('x'), "W");
};

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};