#pragma once
#include <map>
#include <string>
#include <vector>
#include "STATE/state.h"
#include "TAPE/tape.h"

class TMLogic{
private:
    std::vector<State> states;
    std::map<std::string, std:: size_t> index;
    std::vector<std::string> finalStates;
    std::string initialState;
    std::string currentState;
    bool halted;

    const State* FindState(const std::string& name) const;
    bool IsFinal(const std::string& name) const;

public:
    TMLogic();
    TMLogic(const std::vector<State>& states, const std::string& initial, const std::vector<std::string>& finalStates);
    void AddState(const State& s);
    void AddFinalState(const std::string& name);
    void SetInitialState(const std::string& name);

    std::string GetInitialState() const;
    std::string GetCurrentState() const;
    bool IsHalted() const;
    std::size_t GetStatesCount() const;
    std::size_t GetFinalStatesCount() const;
    std::string GetStateName(std::size_t i) const;
    std::string GetFinalStateName(std::size_t i) const;
    
    bool Step(Tape& tape);
    std::size_t Run(Tape& tape, std::size_t maxSteps = 100000);
    void Reset();
};



