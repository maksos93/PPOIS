/**
 * @file word.h
 * @brief Заголовочный файл класса Word.
 *
 * Класс Word описывает одно слово (лексему) англо-русского словаря:
 * его написание, язык и часть речи.
 */

#pragma once
#include <string>

/**
 * @brief Язык слова.
 */
enum class Language {
    English,   ///< Английский
    Russian    ///< Русский
};

/**
 * @brief Часть речи.
 */
enum class PartOfSpeech {
    Unknown,     ///< Не определена
    Noun,        ///< Существительное
    Verb,        ///< Глагол
    Adjective,   ///< Прилагательное
    Adverb,      ///< Наречие
    Pronoun,     ///< Местоимение
    Preposition, ///< Предлог
    Conjunction  ///< Союз
};

/**
 * @brief Слово (лексема).
 */
class Word {
private:
    std::string text;                 ///< Написание слова
    Language language;                ///< Язык слова
    PartOfSpeech partOfSpeech;        ///< Часть речи

public:
    /**
     * @brief Конструктор.
     * @param t Написание слова.
     * @param lang Язык (по умолчанию — английский).
     * @param pos Часть речи (по умолчанию — не определена).
     */
    Word(const std::string& t = "",
         Language lang = Language::English,
         PartOfSpeech pos = PartOfSpeech::Unknown);

    /// @return Написание слова.
    const std::string& GetText() const;

    /// @return Язык слова.
    Language GetLanguage() const;

    /// @return Часть речи.
    PartOfSpeech GetPartOfSpeech() const;

    /// @brief Изменить написание.
    void SetText(const std::string& t);

    /// @brief Изменить часть речи.
    void SetPartOfSpeech(PartOfSpeech pos);

    /// @brief Проверить, что слово непустое.
    bool IsEmpty() const;

    /// @return Часть речи как строка.
    std::string PartOfSpeechToString() const;

    /// @return Язык как строка.
    std::string LanguageToString() const;
};