/**
 * @file tape.h
 * @brief Заголовочный файл класса Tape.
 *
 * Лента машины Тьюринга — это бесконечная в обе стороны
 * последовательность ячеек с символом blank по умолчанию.
 * Внутри реализована как std::vector<char> с автоматическим
 * расширением при выходе головки за границы.
 */
#pragma once
#include <string>
#include <vector>

 /**
  * @brief Лента машины Тьюринга.
  */

class Tape {
private:
    std::vector<char> cells;   ///< Ячейки ленты
    std::size_t head;          ///< Позиция головки (индекс в cells)
    char blank;                ///< Символ пустой ячейки (по умолчанию '_')

public:
    /**
     * @brief Конструктор ленты.
     * @param input Начальное содержимое ленты (по умолчанию пустое).
     * @param blank Символ пустой ячейки (по умолчанию '_').
     */
    Tape(const std::string& input = "", char blank = '_');

    std::size_t GetHead() const;    ///< @return Позиция головки
    char GetBlank() const;          ///< @return Символ пустой ячейки
    std::size_t Size() const;       ///< @return Количество ячеек
    std::string Content() const;    ///< @return Содержимое ленты как строка
    /**
     * @brief Прочитать символ под головкой.
     * @return Символ в текущей ячейке.
     */
    char Read() const;
    /**
     * @brief Записать символ в текущую ячейку.
     * @param symbol Записываемый символ.
     */
    void Write(char symbol);
    /**
     * @brief Сдвинуть головку вправо.
     *
     * Если головка выходит за правую границу, лента
     * расширяется вправо на одну ячейку.
     */
    void MoveRight();
    /**
     * @brief Сдвинуть головку влево.
     *
     * Если головка стоит в позиции 0, лента расширяется
     * влево на одну ячейку (вставляется blank).
     */
    void MoveLeft();
    /**
     * @brief Установить головку в заданную позицию.
     * @param pos Индекс ячейки. При необходимости лента расширяется.
     */
    void SetHead(std::size_t pos);
    /**
     * @brief Очистить ленту: одна ячейка blank, головка в 0.
     */
    void Clear();
};
