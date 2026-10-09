#include "entry.h"
#include <sstream>

Entry::Entry(const Word& eng) : english(eng) {}

void Entry::AddTranslation(const Word& ru) {
    if (!HasTranslation(ru.GetText())) {
        translations.push_back(ru);
    }
}

bool Entry::RemoveTranslation(const std::string& text) {
    for (auto it = translations.begin(); it != translations.end(); ++it) {
        if (it->GetText() == text) {
            translations.erase(it);
            return true;
        }
    }
    return false;
}

void Entry::SetExample(const std::string& ex) { example = ex; }
void Entry::SetTranscription(const std::string& tr) { transcription = tr; }

const Word& Entry::GetEnglish() const { return english; }
const std::vector<Word>& Entry::GetTranslations() const { return translations; }
const std::string& Entry::GetExample() const { return example; }
const std::string& Entry::GetTranscription() const { return transcription; }

bool Entry::HasTranslation(const std::string& text) const {
    for (const auto& t : translations) {
        if (t.GetText() == text) return true;
    }
    return false;
}

std::size_t Entry::TranslationCount() const { return translations.size(); }

std::string Entry::ToString() const {
    std::ostringstream os;
    os << english.GetText();
    if (!transcription.empty()) os << " [" << transcription << "]";
    os << " (" << english.PartOfSpeechToString() << ") — ";
    for (std::size_t i = 0; i < translations.size(); ++i) {
        if (i) os << ", ";
        os << translations[i].GetText();
    }
    if (!example.empty()) os << "\n  Пример: " << example;
    return os.str();
}