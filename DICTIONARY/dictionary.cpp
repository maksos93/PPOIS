#include "dictionary.h"
#include <algorithm>
#include <cctype>
#include <sstream>

std::string Dictionary::ToLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return result;
}

bool Dictionary::AddEntry(const Entry& entry) {
    if (entry.GetEnglish().IsEmpty()) return false;
    entries[ToLower(entry.GetEnglish().GetText())] = entry;
    return true;
}

bool Dictionary::RemoveEntry(const std::string& englishWord) {
    return entries.erase(ToLower(englishWord)) > 0;
}

const Entry* Dictionary::Find(const std::string& englishWord) const {
    auto it = entries.find(ToLower(englishWord));
    if (it == entries.end()) return nullptr;
    return &it->second;
}

std::vector<std::string> Dictionary::Translate(const std::string& englishWord) const {
    std::vector<std::string> result;
    const Entry* e = Find(englishWord);
    if (!e) return result;
    for (const auto& t : e->GetTranslations()) {
        result.push_back(t.GetText());
    }
    return result;
}

std::vector<std::string> Dictionary::ReverseTranslate(const std::string& russianWord) const {
    std::vector<std::string> result;
    std::string target = ToLower(russianWord);
    for (const auto& [key, entry] : entries) {
        for (const auto& t : entry.GetTranslations()) {
            if (ToLower(t.GetText()) == target) {
                result.push_back(entry.GetEnglish().GetText());
                break;
            }
        }
    }
    return result;
}

bool Dictionary::Contains(const std::string& englishWord) const {
    return entries.find(ToLower(englishWord)) != entries.end();
}

std::size_t Dictionary::Size() const { return entries.size(); }

void Dictionary::Clear() { entries.clear(); }

std::vector<std::string> Dictionary::AllWords() const {
    std::vector<std::string> result;
    result.reserve(entries.size());
    for (const auto& [key, entry] : entries) {
        result.push_back(entry.GetEnglish().GetText());
    }
    return result;
}

std::vector<Entry> Dictionary::AllEntries() const {
    std::vector<Entry> result;
    result.reserve(entries.size());
    for (const auto& [key, entry] : entries) {
        result.push_back(entry);
    }
    return result;
}

std::string Dictionary::ToString() const {
    std::ostringstream os;
    for (const auto& [key, entry] : entries) {
        os << entry.ToString() << "\n";
    }
    return os.str();
}