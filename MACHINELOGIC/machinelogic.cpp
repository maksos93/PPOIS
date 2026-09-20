#include "machinelogic.h"

TMLogic::TMLogic():halted(true) {};
TMLogic::TMLogic(const std::vector<State>& states, const std::string& initial, const std::vector<std::string>& finalStates) :
states(states), finalStates(finalStates), initialState(initial), currentState(initial), halted(initial.empty()){
    for(std::size_t i = 0; i < this->states.size(); ++i){
        index[this->states[i].GetName()] = i;
    }
};

void TMLogic::AddState(const State& s){
    index[s.GetName()] = states.size();
    states.push_back(s);
};

void TMLogic::AddFinalState(const std::string& name){
    for(const auto& f : finalStates){
        if(f == name) return;
    }
    finalStates.push_back(name);
};

void TMLogic::SetInitialState(const std::string& name){
    initialState = name;
    currentState = name;
    halted = false;
}

const State* TMLogic::FindState(const std::string& name) const{
    auto it = index.find(name);
    if(it == index.end()) return nullptr;
    return &states[it->second];
};

bool TMLogic::IsFinal(const std::string& name) const {
    for(const auto& f : finalStates){
        if(f == name) return true;
    }
    return false;
};

std::string TMLogic::GetInitialState() const {
    return initialState;
};

std::string TMLogic::GetCurrentState() const {
    return currentState;
};

bool TMLogic::IsHalted() const {
    return halted;
};

std::size_t TMLogic::GetStatesCount() const {
    return states.size();
};

std::size_t TMLogic::GetFinalStatesCount() const {
    return finalStates.size();
};

std::string TMLogic::GetStateName(std::size_t i) const {
    return states.at(i).GetName();
};

std::string TMLogic::GetFinalStateName(std::size_t i) const {
    return finalStates.at(i);
};

bool TMLogic::Step(Tape& tape){
    if(halted) return false;

    if(IsFinal(currentState)){
        halted = true;
        return false;
    }

    const State* st = FindState(currentState);
    if(st == nullptr){
        halted = true;
        return false;
    }

    char symbol = tape.Read();
    if(!st->HasTransition(symbol)){
        halted = true;
        return false;
    }

    auto writeOpt = st->GetWrite(symbol);
    auto moveOpt  = st->GetMove(symbol);
    auto nextOpt  = st->GetNext(symbol);

    if (!writeOpt || !moveOpt || !nextOpt) {
    halted = true;
    return false;
    }

    char write = *writeOpt;
    char move  = *moveOpt;
    std::string next = *nextOpt;

    tape.Write(write);

    if(move == 'L' || move == 'l') tape.MoveLeft();
    else if(move == 'R' || move == 'r') tape.MoveRight();

    currentState = next;
    if(IsFinal(currentState))halted = true;
    return true;
};

std::size_t TMLogic::Run(Tape& tape, std::size_t maxSteps){
    std::size_t steps = 0;
    while(!halted && steps < maxSteps){
        if (!Step(tape)) break;
        ++steps;
    }
    return steps;
};

void TMLogic::Reset(){
    currentState = initialState;
    halted = initialState.empty() || IsFinal(initialState);
};
