#include "tape.h"
#include <string>

Tape::Tape(const std::string& input, char blank)
    :head(0), blank(blank) {
    if(input.empty()){
        cells.push_back(blank);
    }
    else {
        cells.assign(input.begin(), input.end());
    }
};

std::size_t Tape::GetHead() const{
    return head;
};

char Tape::GetBlank() const {
    return blank;
};

std::size_t Tape::Size() const {
    return cells.size();
};

std::string Tape::Content() const {
    return std::string(cells.begin(), cells.end());
};

char Tape::Read() const {
    return cells[head];
};

void Tape::Write(char symbol) {
    cells[head] = symbol;
};

void Tape::MoveLeft() {
    if (head == 0) cells.insert(cells.begin(), blank);
    else{
        --head;
    }
};

void Tape::MoveRight() {
    ++head;
    if(head > cells.size()) cells.push_back(blank);
};

void Tape::SetHead(std::size_t pos){
    while(cells.size() <= pos)cells.push_back(blank);
    head = pos;
};

void Tape::Clear(){
    cells.assign(1,blank);
    head = 0;
};