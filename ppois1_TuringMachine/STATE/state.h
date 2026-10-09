/**
 * @file state.h
 * @brief Заголовочный файл класса State.
 *
 * Класс State описывает одно состояние машины Тьюринга
 * и хранит таблицу переходов из него.
 */
#pragma once
#include <map>
#include <string>
#include <optional>

 /**
  * @brief Состояние машины Тьюринга.
  *
  * Каждое состояние содержит набор переходов вида
  * (read → write, move, next). Переходы хранятся в трёх
  * ассоциативных контейнерах, ключом в которых является
  * считываемый символ.
  */

class State{
private:
    std::map<char, char> writeMap;         ///< Что записать на ленту
    std::map<char, char> moveMap;          ///< Куда двигать головку: 'L' или 'R'
    std::map<char, std::string> nextMap;   ///< В какое состояние перейти
    std::string name;                      ///< Имя состояния (например, "q0")

public:
    /**
    * @brief Конструктор состояния.
    * @param n Имя состояния (по умолчанию пустое).
    */

    State(const std::string& n = "");
    /**
    * 
    * @brief Добавить переход из состояния.
    * @param read  Считываемый символ.
    * @param write Записываемый символ.
    * @param move  Направление движения: 'L' или 'R'.
    * @param next  Имя следующего состояния.
    */

    void AddTransition(char read, char write, char move, const std::string& next);
    /**
     * @brief Проверить, есть ли переход по заданному символу.
     * @param read Считываемый символ.
     * @return true, если переход существует.
     */
    bool HasTransition(char read) const;
    /**
     * @brief Получить записываемый символ для перехода.
     * @param read Считываемый символ.
     * @return std::optional с символом или std::nullopt, если перехода нет.
     */
    std::optional<char> GetWrite(char read) const;
    /**
     * @brief Получить направление движения для перехода.
     * @param read Считываемый символ.
     * @return std::optional с 'L'/'R' или std::nullopt.
     */
    std::optional<char> GetMove(char read) const;
    /**
     * @brief Получить имя следующего состояния.
     * @param read Считываемый символ.
     * @return std::optional с именем или std::nullopt.
     */
    std::optional<std::string> GetNext(char read) const;
    /**
     * @brief Получить имя состояния.
     * @return Константная ссылка на имя.
     */
    const std::string& GetName() const;
};