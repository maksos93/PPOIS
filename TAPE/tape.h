#pragma once
#include <string>
#include <vector>

class Tape {
private:
    std::vector<char> cells;
    std::size_t head;
    char blank;

public:
    Tape(const std::string& input = "", char blank = '_');

    std::size_t GetHead() const;
    char GetBlank() const;
    std::size_t Size() const;
    std::string Content() const;
    char Read() const;
    void Write(char symbol);
    void MoveRight();
    void MoveLeft();
    void SetHead(std::size_t pos);
    void Clear();
};
