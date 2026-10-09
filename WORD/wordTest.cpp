#include <gtest/gtest.h>
#include "word.h"

TEST(WordTest, DefaultConstructor) {
    Word w;
    EXPECT_TRUE(w.IsEmpty());
    EXPECT_EQ(w.GetLanguage(), Language::English);
    EXPECT_EQ(w.GetPartOfSpeech(), PartOfSpeech::Unknown);
}

TEST(WordTest, ConstructWithParams) {
    Word w("hello", Language::English, PartOfSpeech::Noun);
    EXPECT_EQ(w.GetText(), "hello");
    EXPECT_EQ(w.GetLanguage(), Language::English);
    EXPECT_EQ(w.GetPartOfSpeech(), PartOfSpeech::Noun);
    EXPECT_FALSE(w.IsEmpty());
}

TEST(WordTest, SetText) {
    Word w("cat");
    w.SetText("dog");
    EXPECT_EQ(w.GetText(), "dog");
}

TEST(WordTest, PartOfSpeechToString) {
    Word w("run", Language::English, PartOfSpeech::Verb);
    EXPECT_EQ(w.PartOfSpeechToString(), "глаг.");
}

TEST(WordTest, LanguageToString) {
    Word w("кот", Language::Russian, PartOfSpeech::Noun);
    EXPECT_EQ(w.LanguageToString(), "ru");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}