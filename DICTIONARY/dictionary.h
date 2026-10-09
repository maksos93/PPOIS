/**
 * @file dictionary.h
 * @brief Заголовочный файл класса Dictionary.
 *
 * Dictionary — сам англо-русский словарь: хранит набор
 * словарных статей (@ref Entry) и предоставляет операции
 * поиска, добавления, удаления и перевода.
 */

#pragma once
#include <map>
#include <string>
#include <vector>
#include "ENTRY/entry.h"

/**
 * @brief Англо-русский словарь.
 */
class Dictionary {
private:
    std::map<std::string, Entry> entries;   ///< Индекс: англ. слово → статья

    /// @brief Привести строку к нижнему регистру.
    static std::string ToLower(const std::string& s);

public:
    Dictionary() = default;

    /**
     * @brief Добавить статью в словарь.
     * @param entry Статья (должна содержать английское слово).
     * @return true, если статья добавлена (или заменена).
     */
    bool AddEntry(const Entry& entry);

    /**
     * @brief Удалить статью.
     * @param englishWord Английское слово.
     * @return true, если статья была и удалена.
     */
    bool RemoveEntry(const std::string& englishWord);

    /**
     * @brief Найти статью.
     * @param englishWord Английское слово.
     * @return Указатель на статью или nullptr.
     */
    const Entry* Find(const std::string& englishWord) const;

    /**
     * @brief Перевести английское слово на русский.
     * @param englishWord Английское слово.
     * @return Вектор переводов (пустой, если слова нет).
     */
    std::vector<std::string> Translate(const std::string& englishWord) const;

    /**
     * @brief Найти английские слова по русскому переводу.
     * @param russianWord Русское слово.
     * @return Вектор английских слов.
     */
    std::vector<std::string> ReverseTranslate(const std::string& russianWord) const;

    /**
     * @brief Проверить наличие слова.
     */
    bool Contains(const std::string& englishWord) const;

    /// @return Количество статей.
    std::size_t Size() const;

    /// @brief Очистить словарь.
    void Clear();

    /// @return Все английские слова (отсортированы).
    std::vector<std::string> AllWords() const;

    /// @return Все статьи.
    std::vector<Entry> AllEntries() const;

    /// @brief Вывести словарь в виде строки.
    std::string ToString() const;
};