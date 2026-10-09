#include <gtest/gtest.h>
#include "dictionary.h"

static Dictionary MakeDict() {
    Dictionary d;
    Entry cat(Word("cat", Language::English, PartOfSpeech::Noun));
    cat.AddTranslation(Word("кот", Language::Russian));
    cat.AddTranslation(Word("кошка", Language::Russian));
    d.AddEntry(cat);

    Entry dog(Word("dog", Language::English, PartOfSpeech::Noun));
    dog.AddTranslation(Word("собака", Language::Russian));
    d.AddEntry(dog);

    Entry run(Word("run", Language::English, PartOfSpeech::Verb));
    run.AddTranslation(Word("бежать", Language::Russian));
    d.AddEntry(run);

    return d;
}

TEST(DictionaryTest, EmptyDictionary) {
    Dictionary d;
    EXPECT_EQ(d.Size(), 0u);
    EXPECT_FALSE(d.Contains("cat"));
}

TEST(DictionaryTest, AddAndSize) {
    Dictionary d = MakeDict();
    EXPECT_EQ(d.Size(), 3u);
    EXPECT_TRUE(d.Contains("cat"));
    EXPECT_TRUE(d.Contains("dog"));
    EXPECT_TRUE(d.Contains("run"));
}

TEST(DictionaryTest, AddEmptyWord) {
    Dictionary d;
    Entry e(Word(""));
    EXPECT_FALSE(d.AddEntry(e));
    EXPECT_EQ(d.Size(), 0u);
}

TEST(DictionaryTest, Translate) {
    Dictionary d = MakeDict();
    auto tr = d.Translate("cat");
    EXPECT_EQ(tr.size(), 2u);
    EXPECT_EQ(tr[0], "кот");
}

TEST(DictionaryTest, TranslateCaseInsensitive) {
    Dictionary d = MakeDict();
    auto tr = d.Translate("CAT");
    EXPECT_EQ(tr.size(), 2u);
}

TEST(DictionaryTest, TranslateUnknown) {
    Dictionary d = MakeDict();
    auto tr = d.Translate("unknown");
    EXPECT_TRUE(tr.empty());
}

TEST(DictionaryTest, ReverseTranslate) {
    Dictionary d = MakeDict();
    auto en = d.ReverseTranslate("собака");
    ASSERT_EQ(en.size(), 1u);
    EXPECT_EQ(en[0], "dog");
}

TEST(DictionaryTest, RemoveEntry) {
    Dictionary d = MakeDict();
    EXPECT_TRUE(d.RemoveEntry("cat"));
    EXPECT_EQ(d.Size(), 2u);
    EXPECT_FALSE(d.RemoveEntry("cat"));
}

TEST(DictionaryTest, Find) {
    Dictionary d = MakeDict();
    const Entry* e = d.Find("cat");
    ASSERT_NE(e, nullptr);
    EXPECT_EQ(e->GetEnglish().GetText(), "cat");

    EXPECT_EQ(d.Find("unknown"), nullptr);
}

TEST(DictionaryTest, Clear) {
    Dictionary d = MakeDict();
    d.Clear();
    EXPECT_EQ(d.Size(), 0u);
}

TEST(DictionaryTest, AllWordsSorted) {
    Dictionary d = MakeDict();
    auto words = d.AllWords();
    EXPECT_EQ(words.size(), 3u);
    EXPECT_EQ(words[0], "cat");
    EXPECT_EQ(words[1], "dog");
    EXPECT_EQ(words[2], "run");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}