/**
 * @file machinelogic.h
 * @brief Заголовочный файл класса TMLogic.
 *
 * Класс TMLogic управляет работой машины Тьюринга:
 * хранит состояния, финальные состояния, начальное
 * состояние и выполняет шаги машины.
 */
#pragma once
#include <map>
#include <string>
#include <vector>
#include "ppois1_TuringMachine/STATE/state.h"
#include "ppois1_TuringMachine/TAPE/tape.h"

 /**
  * @brief Логика машины Тьюринга.
  *
  * Содержит набор состояний (@ref State), индексирует их
  * по имени, хранит начальное и текущее состояние,
  * а также список финальных состояний.
  */

class TMLogic{
private:
    std::vector<State> states;                     ///< Все состояния машины
    std::map<std::string, std::size_t> index;      ///< Имя → индекс в states
    std::vector<std::string> finalStates;          ///< Список финальных состояний
    std::string initialState;                      ///< Имя начального состояния
    std::string currentState;                      ///< Имя текущего состояния
    bool halted;                                   ///< Остановлена ли машина

    /**
     * @brief Найти состояние по имени.
     * @param name Имя состояния.
     * @return Указатель на состояние или nullptr.
     */

    const State* FindState(const std::string& name) const;
    /**
     * @brief Проверить, является ли состояние финальным.
     * @param name Имя состояния.
     * @return true, если состояние финальное.
     */
    bool IsFinal(const std::string& name) const;

public:
    /// @brief Конструктор по умолчанию: пустая машина, остановлена.
    TMLogic();
    /**
     * @brief Конструктор с параметрами.
     * @param states       Набор состояний.
     * @param initial      Имя начального состояния.
     * @param finalStates  Список финальных состояний.
     */
    TMLogic(const std::vector<State>& states, const std::string& initial, const std::vector<std::string>& finalStates);
    /**
     * @brief Добавить состояние.
     * @param s Состояние для добавления.
     */
    void AddState(const State& s);
    /**
     * @brief Пометить состояние финальным.
     * @param name Имя состояния.
     */
    void AddFinalState(const std::string& name);
    /**
     * @brief Задать начальное состояние.
     * @param name Имя состояния.
     */
    void SetInitialState(const std::string& name);

    std::string GetInitialState() const;                    ///< @return Имя начального состояния
    std::string GetCurrentState() const;                    ///< @return Имя текущего состояния
    bool IsHalted() const;                                  ///< @return true, если машина остановлена
    std::size_t GetStatesCount() const;                     ///< @return Количество состояний
    std::size_t GetFinalStatesCount() const;                ///< @return Количество финальных состояний
    std::string GetStateName(std::size_t i) const;          ///< @param i Индекс @return Имя состояния
    std::string GetFinalStateName(std::size_t i) const;     ///< @param i Индекс @return Имя финального состояния
    
    /**
     * @brief Выполнить один шаг машины на ленте.
     *
     * Читает символ, ищет переход, записывает символ,
     * двигает головку, меняет состояние.
     *
     * @param tape Лента, на которой работает машина.
     * @return true, если шаг выполнен; false, если машина остановилась.
     */
    bool Step(Tape& tape);
    /**
     * @brief Запустить машину до остановки или до лимита шагов.
     * @param tape     Лента.
     * @param maxSteps Максимальное число шагов (по умолчанию 100000).
     * @return Количество фактически выполненных шагов.
     */
    std::size_t Run(Tape& tape, std::size_t maxSteps = 100000);
    /**
     * @brief Сбросить машину в начальное состояние.
     *
     * Устанавливает currentState = initialState и сбрасывает halted.
     * Ленту не трогает.
     */
    void Reset();
};