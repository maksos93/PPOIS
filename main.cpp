#include <iostream>
#include <limits>
#include <string>
#include <vector>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

#include "DICTIONARY/dictionary.h"

static void setupConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void printMenu() {
    std::cout << "\n===== Англо-русский словарь =====\n"
              << "1.  Показать весь словарь\n"
              << "2.  Добавить слово\n"
              << "3.  Добавить перевод к слову\n"
              << "4.  Найти слово (EN → RU)\n"
              << "5.  Обратный поиск (RU → EN)\n"
              << "6.  Удалить слово\n"
              << "7.  Количество слов\n"
              << "8.  Загрузить пример\n"
              << "9.  Очистить словарь\n"
              << "0.  Выход\n"
              << "Выбор: ";
}

static void showAll(const Dictionary& d) {
    if (d.Size() == 0) {
        std::cout << "Словарь пуст.\n";
        return;
    }
    std::cout << "Всего слов: " << d.Size() << "\n";
    for (const auto& e : d.AllEntries()) {
        std::cout << "  " << e.ToString() << "\n";
    }
}

static Dictionary makeExample() {
    Dictionary d;

    Entry hello(Word("hello", Language::English, PartOfSpeech::Noun));
    hello.AddTranslation(Word("привет", Language::Russian));
    hello.AddTranslation(Word("здравствуйте", Language::Russian));
    hello.SetTranscription("həˈloʊ");
    hello.SetExample("Hello, world!");
    d.AddEntry(hello);

    Entry cat(Word("cat", Language::English, PartOfSpeech::Noun));
    cat.AddTranslation(Word("кот", Language::Russian));
    cat.AddTranslation(Word("кошка", Language::Russian));
    cat.SetTranscription("kæt");
    cat.SetExample("The cat is sleeping.");
    d.AddEntry(cat);

    Entry run(Word("run", Language::English, PartOfSpeech::Verb));
    run.AddTranslation(Word("бежать", Language::Russian));
    run.AddTranslation(Word("бегать", Language::Russian));
    run.SetTranscription("rʌn");
    run.SetExample("I run every morning.");
    d.AddEntry(run);

    Entry book(Word("book", Language::English, PartOfSpeech::Noun));
    book.AddTranslation(Word("книга", Language::Russian));
    book.SetTranscription("bʊk");
    d.AddEntry(book);

    return d;
}

int main() {
    setupConsole();
    Dictionary dict;

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
            showAll(dict);

        } else if (choice == 2) {
            std::string word, transcription;
            std::cout << "Английское слово: ";
            std::getline(std::cin, word);
            if (word.empty()) { std::cout << "Пустое слово.\n"; continue; }
            if (dict.Contains(word)) {
                std::cout << "Слово уже есть. Используйте пункт 3.\n";
                continue;
            }
            Entry e(Word(word, Language::English, PartOfSpeech::Noun));
            std::cout << "Транскрипция (Enter — пропустить): ";
            std::getline(std::cin, transcription);
            if (!transcription.empty()) e.SetTranscription(transcription);
            dict.AddEntry(e);
            std::cout << "Слово добавлено.\n";

        } else if (choice == 3) {
            std::string word, translation;
            std::cout << "Английское слово: ";
            std::getline(std::cin, word);
            const Entry* existing = dict.Find(word);
            if (!existing) {
                std::cout << "Слова нет в словаре. Сначала добавьте (пункт 2).\n";
                continue;
            }
            Entry updated = *existing;
            std::cout << "Русский перевод: ";
            std::getline(std::cin, translation);
            if (translation.empty()) { std::cout << "Пустой перевод.\n"; continue; }
            updated.AddTranslation(Word(translation, Language::Russian));
            dict.AddEntry(updated);
            std::cout << "Перевод добавлен.\n";

        } else if (choice == 4) {
            std::string word;
            std::cout << "Английское слово: ";
            std::getline(std::cin, word);
            const Entry* e = dict.Find(word);
            if (!e) {
                std::cout << "Слово не найдено.\n";
            } else {
                std::cout << e->ToString() << "\n";
            }

        } else if (choice == 5) {
            std::string word;
            std::cout << "Русское слово: ";
            std::getline(std::cin, word);
            auto result = dict.ReverseTranslate(word);
            if (result.empty()) {
                std::cout << "Ничего не найдено.\n";
            } else {
                std::cout << "Английские варианты:";
                for (const auto& w : result) std::cout << ' ' << w;
                std::cout << "\n";
            }

        } else if (choice == 6) {
            std::string word;
            std::cout << "Английское слово для удаления: ";
            std::getline(std::cin, word);
            if (dict.RemoveEntry(word)) {
                std::cout << "Удалено.\n";
            } else {
                std::cout << "Слово не найдено.\n";
            }

        } else if (choice == 7) {
            std::cout << "Слов в словаре: " << dict.Size() << "\n";

        } else if (choice == 8) {
            dict = makeExample();
            std::cout << "Пример загружен: 4 слова.\n";

        } else if (choice == 9) {
            dict.Clear();
            std::cout << "Словарь очищен.\n";

        } else {
            std::cout << "Неизвестный пункт меню.\n";
        }
    }
    return 0;
}