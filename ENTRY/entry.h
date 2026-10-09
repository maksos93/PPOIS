/**
 * @file entry.h
 * @brief Заголовочный файл класса Entry.
 *
 * Entry — словарная статья: английское слово, его переводы
 * на русский (одно или несколько) и пример употребления.
 */

#pragma once
#include <string>
#include <vector>
#include "WORD/word.h"

/**
 * @brief Словарная статья.
 */
class Entry {
private:
    Word english;                          ///< Английское слово
    std::vector<Word> translations;        ///< Переводы на русский
    std::string example;                   ///< Пример употребления
    std::string transcription;             ///< Транскрипция

public:
    Entry() = default;

    /**
     * @brief Конструктор.
     * @param eng Английское слово.
     */
    explicit Entry(const Word& eng);

    /// @brief Добавить перевод.
    void AddTranslation(const Word& ru);

    /// @brief Удалить перевод по тексту.
    bool RemoveTranslation(const std::string& text);

    /// @brief Задать пример употребления.
    void SetExample(const std::string& ex);

    /// @brief Задать транскрипцию.
    void SetTranscription(const std::string& tr);

    /// @return Английское слово.
    const Word& GetEnglish() const;

    /// @return Список переводов.
    const std::vector<Word>& GetTranslations() const;

    /// @return Пример употребления.
    const std::string& GetExample() const;

    /// @return Транскрипция.
    const std::string& GetTranscription() const;

    /// @brief Есть ли перевод с таким текстом.
    bool HasTranslation(const std::string& text) const;

    /// @return Количество переводов.
    std::size_t TranslationCount() const;

    /// @brief Форматированный вывод статьи.
    std::string ToString() const;
};