#include <gtest/gtest.h>
#include "entry.h"

TEST(EntryTest, ConstructEmpty) {
    Entry e;
    EXPECT_TRUE(e.GetEnglish().IsEmpty());
    EXPECT_EQ(e.TranslationCount(), 0u);
}

TEST(EntryTest, AddTranslation) {
    Entry e(Word("hello", Language::English, PartOfSpeech::Noun));
    e.AddTranslation(Word("привет", Language::Russian));
    e.AddTranslation(Word("здравствуйте", Language::Russian));
    EXPECT_EQ(e.TranslationCount(), 2u);
    EXPECT_TRUE(e.HasTranslation("привет"));
    EXPECT_TRUE(e.HasTranslation("здравствуйте"));
    EXPECT_FALSE(e.HasTranslation("пока"));
}

TEST(EntryTest, AddDuplicateTranslation) {
    Entry e(Word("hello"));
    e.AddTranslation(Word("привет"));
    e.AddTranslation(Word("привет"));
    EXPECT_EQ(e.TranslationCount(), 1u);
}

TEST(EntryTest, RemoveTranslation) {
    Entry e(Word("hello"));
    e.AddTranslation(Word("привет"));
    e.AddTranslation(Word("здравствуйте"));
    EXPECT_TRUE(e.RemoveTranslation("привет"));
    EXPECT_EQ(e.TranslationCount(), 1u);
    EXPECT_FALSE(e.HasTranslation("привет"));
    EXPECT_FALSE(e.RemoveTranslation("нет"));
}

TEST(EntryTest, Example) {
    Entry e(Word("cat"));
    e.SetExample("The cat sleeps.");
    EXPECT_EQ(e.GetExample(), "The cat sleeps.");
}

TEST(EntryTest, ToString) {
    Entry e(Word("cat", Language::English, PartOfSpeech::Noun));
    e.AddTranslation(Word("кот", Language::Russian));
    e.AddTranslation(Word("кошка", Language::Russian));
    std::string s = e.ToString();
    EXPECT_NE(s.find("cat"), std::string::npos);
    EXPECT_NE(s.find("кот"), std::string::npos);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}