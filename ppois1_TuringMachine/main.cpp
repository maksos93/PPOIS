#include <iostream>
#include <limits>
#include <string>

#include "MACHINELOGIC/machinelogic.h"

static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void printMenu() {
    std::cout << "\n===== Машина Тьюринга =====\n"
              << "1. Показать машину\n"
              << "2. Добавить состояние\n"
              << "3. Добавить переход\n"
              << "4. Отметить состояние завершающим\n"
              << "5. Задать начальное состояние\n"
              << "6. Запустить на ленте\n"
              << "7. Один шаг\n"
              << "8. Сбросить машину\n"
              << "9. Загрузить пример (замена 1 -> 0)\n"
              << "0. Выход\n"
              << "Выбор: ";
}

static void showMachine(const TMLogic& tm) {
    std::cout << "Начальное состояние: " << tm.GetInitialState() << '\n';
    std::cout << "Текущее состояние  : " << tm.GetCurrentState() << '\n';
    std::cout << "Остановлена        : " << (tm.IsHalted() ? "да" : "нет") << '\n';
    std::cout << "Состояния:";
    for (std::size_t i = 0; i < tm.GetStatesCount(); ++i) {
        std::cout << ' ' << tm.GetStateName(i);
    }
    std::cout << "\nЗавершающие:";
    for (std::size_t i = 0; i < tm.GetFinalStatesCount(); ++i) {
        std::cout << ' ' << tm.GetFinalStateName(i);
    }
    std::cout << '\n';
}

static TMLogic makeExample() {
    State q0("q0");
    q0.AddTransition('1', '0', 'R', "q0");
    q0.AddTransition('_', '_', 'R', "q1");

    State q1("q1");

    std::vector<State> states = { q0, q1 };
    std::vector<std::string> finals = { "q1" };
    return TMLogic(states, "q0", finals);
}

int main() {
    TMLogic tm;

    while (true) {
        printMenu();
        int choice;
        if (!(std::cin >> choice)) {
            clearInput();
            std::cout << "Некорректный ввод.\n";
            continue;
        }
        clearInput();

        if (choice == 0) {
            std::cout << "Выход.\n";
            return 0;
        }

        if (choice == 1) {
            showMachine(tm);

        } else if (choice == 2) {
            std::string name;
            std::cout << "Имя состояния: ";
            std::getline(std::cin, name);
            tm.AddState(State(name));
            std::cout << "Состояние добавлено.\n";

        } else if (choice == 3) {
            std::string from, next;
            char read, write, move;
            std::cout << "Из состояния: ";
            std::getline(std::cin, from);
            std::cout << "Считываемый символ: ";
            std::cin >> read;
            std::cout << "Записываемый символ: ";
            std::cin >> write;
            std::cout << "Направление (L/R): ";
            std::cin >> move;
            clearInput();
            std::cout << "В состояние: ";
            std::getline(std::cin, next);

            std::vector<State> newStates;
            bool found = false;
            for (std::size_t i = 0; i < tm.GetStatesCount(); ++i) {
                if (tm.GetStateName(i) == from) {
                    State s(from);
                    s.AddTransition(read, write, move, next);
                    newStates.push_back(s);
                    found = true;
                } else {
                    newStates.push_back(State(tm.GetStateName(i)));
                }
            }
            if (!found) {
                State s(from);
                s.AddTransition(read, write, move, next);
                newStates.push_back(s);
            }

            std::vector<std::string> finals;
            for (std::size_t i = 0; i < tm.GetFinalStatesCount(); ++i) {
                finals.push_back(tm.GetFinalStateName(i));
            }
            tm = TMLogic(newStates, tm.GetInitialState(), finals);
            std::cout << "Переход добавлен.\n";

        } else if (choice == 4) {
            std::string name;
            std::cout << "Имя завершающего состояния: ";
            std::getline(std::cin, name);
            tm.AddFinalState(name);
            std::cout << "Отмечено.\n";

        } else if (choice == 5) {
            std::string name;
            std::cout << "Имя начального состояния: ";
            std::getline(std::cin, name);
            tm.SetInitialState(name);
            std::cout << "Задано.\n";

        } else if (choice == 6) {
            std::string input;
            std::size_t maxSteps;
            std::cout << "Содержимое ленты (_ для пустой): ";
            std::getline(std::cin, input);
            if (input.empty()) input = "_";
            std::cout << "Максимум шагов: ";
            std::cin >> maxSteps;
            clearInput();

            Tape tape(input);
            tm.Reset();
            std::size_t steps = tm.Run(tape, maxSteps);
            std::cout << "Выполнено шагов: " << steps << '\n';
            std::cout << "Лента: " << tape.Content() << '\n';
            std::cout << "Остановлена: " << (tm.IsHalted() ? "да" : "нет") << '\n';

        } else if (choice == 7) {
            std::string input;
            std::cout << "Содержимое ленты (_ для пустой): ";
            std::getline(std::cin, input);
            if (input.empty()) input = "_";

            Tape tape(input);
            bool ok = tm.Step(tape);
            std::cout << (ok ? "Шаг выполнен." : "Машина остановлена.") << '\n';
            std::cout << "Лента: " << tape.Content() << '\n';

        } else if (choice == 8) {
            tm.Reset();
            std::cout << "Машина сброшена.\n";

        } else if (choice == 9) {
            tm = makeExample();
            std::cout << "Пример загружен: заменяет все '1' на '0'.\n";

        } else {
            std::cout << "Неизвестный пункт меню.\n";
        }
    }
    return 0;
};