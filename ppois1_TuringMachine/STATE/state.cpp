#include "state.h"
#include <string>
#include <optional>
State::State(const std::string& n) : name(n) {}

void State::AddTransition(char read, char write, char move, const std::string& next) {
    writeMap[read] = read;
    moveMap[read] = move;
    nextMap[read] = next;
};

bool State::HasTransition(char read) const {
    return writeMap.find(read) != writeMap.end();
};

std::optional<char> State::GetWrite(char read) const {
    auto it = writeMap.find(read);
    if(it == writeMap.end()) return std::nullopt;
    return it -> second;
};

std::optional<char> State::GetMove(char read) const {
    auto it = moveMap.find(read);
    if(it == moveMap.end()) return std::nullopt;
    return it -> second;
};

std::optional<std::string> State::GetNext(char read) const {
    auto it = nextMap.find(read);
    if(it == nextMap.end()) return std::nullopt;
    return it -> second;
};

const std::string& State::GetName() const {
    return name;
};