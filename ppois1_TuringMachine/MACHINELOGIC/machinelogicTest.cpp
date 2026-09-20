#include <gtest/gtest.h>
#include "machinelogic.h"

static TMLogic MakeSimpleTM() {
    State q0("q0");
    q0.AddTransition('1', '0', 'R', "q0");
    q0.AddTransition('_', '_', 'R', "q1");

    State q1("q1");

    std::vector<State> states = {q0, q1};
    std::vector<std::string> finals = {"q1"};
    return TMLogic(states, "q0", finals);
};

TEST(TMLogicTest, DefaultConstructor){
    TMLogic tm;
    EXPECT_EQ(tm.GetStatesCount(), 0u);
    EXPECT_TRUE(tm.IsHalted());
};

TEST(TMLogicTest, ConstructorWithParams){
    TMLogic tm = MakeSimpleTM();
    EXPECT_EQ(tm.GetStatesCount(), 2u);
    EXPECT_EQ(tm.GetFinalStatesCount(), 1u);
    EXPECT_EQ(tm.GetInitialState(), "q0");
    EXPECT_EQ(tm.GetCurrentState(), "q0");
    EXPECT_FALSE(tm.IsHalted());
};

TEST(TMLogicTest, AddStateAndFinal){
    TMLogic tm;
    tm.AddState(State("q0"));
    tm.AddState(State("q1"));
    tm.SetInitialState("q0");
    tm.AddFinalState("q1");
    tm.AddFinalState("q1");
    EXPECT_EQ(tm.GetStatesCount(), 2u);
    EXPECT_EQ(tm.GetFinalStatesCount(), 1u);
    EXPECT_FALSE(tm.IsHalted());
};

TEST(TMLogicTest, GetStateName){
    TMLogic tm = MakeSimpleTM();
    Tape tape("11");

    EXPECT_TRUE(tm.Step(tape));
    EXPECT_EQ(tape.Content()[0], '0');
    EXPECT_EQ(tm.GetCurrentState(), "q0");

    EXPECT_TRUE(tm.Step(tape));
    EXPECT_EQ(tape.Content()[1], '0');

    EXPECT_TRUE(tm.Step(tape));
    EXPECT_EQ(tm.GetCurrentState(), "q1");
    EXPECT_TRUE(tm.IsHalted());

    EXPECT_FALSE(tm.Step(tape));
};

TEST(TMLogicTEST, StepWithoutTransitionHalts){
    State q0("q0");
    q0.AddTransition('1', '0', 'R', "q0");
    std::vector<State> states = {q0};
    TMLogic tm(states, "q0", {});

    Tape tape("0");
    EXPECT_FALSE(tm.Step(tape));
    EXPECT_TRUE(tm.IsHalted());
};

TEST(TMLogicTest, Run){
    TMLogic tm = MakeSimpleTM();
    Tape tape("111");
    tm.Run(tape);
    EXPECT_EQ(tape.Content().substr(0, 3), "000");
    EXPECT_TRUE(tm.IsHalted());
};

TEST(TMLogicTest, RunWithStepLimit){
    State q0("q0");
    q0.AddTransition('1', '1', 'R', "q0");
    std::vector<State> states = {q0};
    TMLogic tm(states, "q0", {});

    Tape tape("1");
    std::size_t steps = tm.Run(tape, 10);
    EXPECT_EQ(steps, 10u);
    EXPECT_FALSE(tm.IsHalted());
};

TEST(TMLogicTest, Reset){
    TMLogic tm = MakeSimpleTM();
    Tape tape("11");
    tm.Step(tape);
    tm.Reset();
    EXPECT_EQ(tm.GetCurrentState(), "q0");
    EXPECT_FALSE(tm.IsHalted());
};

TEST(TMLogicTest, StepMoveLeft){
    State q0("q0");
    q0.AddTransition('1', '0', 'L', "q1");
    State q1("q1");
    std::vector<State> states = {q0, q1};
    std::vector<std::string> finals = {"q1"};
    TMLogic tm(states, "q0", finals);

    Tape tape("11");
    tm.Step(tape);
    EXPECT_EQ(tape.GetHead(), 0u);
    EXPECT_EQ(tape.Content()[0], '0');
    EXPECT_TRUE(tm.IsHalted());
};

TEST(TMLogicTest, AlreadyFinalUnitialState){
    State q0("q0");
    std::vector<State> states = {q0};
    std::vector<std::string> finals = {"q0"};
    TMLogic tm(states, "q0", finals);

    Tape tape("1");
    EXPECT_FALSE(tm.Step(tape));
    EXPECT_TRUE(tm.IsHalted());
};

TEST(TMLogicTest, FindStateViaStep){
    TMLogic tm = MakeSimpleTM();
    Tape tape("1");
    EXPECT_TRUE(tm.Step(tape));
    EXPECT_EQ(tm.GetCurrentState(), "q0");
};

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};