#include "word.h"

Word::Word(const std::string& t, Language lang, PartOfSpeech pos)
    : text(t), language(lang), partOfSpeech(pos) {}

const std::string& Word::GetText() const { return text; }
Language Word::GetLanguage() const { return language; }
PartOfSpeech Word::GetPartOfSpeech() const { return partOfSpeech; }

void Word::SetText(const std::string& t) { text = t; }
void Word::SetPartOfSpeech(PartOfSpeech pos) { partOfSpeech = pos; }

bool Word::IsEmpty() const { return text.empty(); }

std::string Word::PartOfSpeechToString() const {
    switch (partOfSpeech) {
        case PartOfSpeech::Noun:        return "сущ.";
        case PartOfSpeech::Verb:        return "глаг.";
        case PartOfSpeech::Adjective:   return "прил.";
        case PartOfSpeech::Adverb:      return "нареч.";
        case PartOfSpeech::Pronoun:     return "мест.";
        case PartOfSpeech::Preposition: return "предлог";
        case PartOfSpeech::Conjunction: return "союз";
        default:                        return "—";
    }
}

std::string Word::LanguageToString() const {
    return language == Language::English ? "en" : "ru";
}