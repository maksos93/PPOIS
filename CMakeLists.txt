cmake_minimum_required(VERSION 3.16)
project(TuringMachine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- GoogleTest через FetchContent ---
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# --- Библиотека классов ---
add_library(turing_core
    ppois1_TuringMachine/STATE/state.cpp
    ppois1_TuringMachine/TAPE/tape.cpp
    ppois1_TuringMachine/MACHINELOGIC/machinelogic.cpp
)
target_include_directories(turing_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# --- Консольная программа ---
add_executable(turing_main ppois1_TuringMachine/main.cpp)
target_link_libraries(turing_main PRIVATE turing_core)

# --- Тесты ---
add_executable(state_tests ppois1_TuringMachine/STATE/stateTest.cpp)
target_link_libraries(state_tests PRIVATE turing_core gtest )
add_test(NAME state_tests COMMAND state_tests)

add_executable(tape_tests ppois1_TuringMachine/TAPE/tapeTest.cpp)
target_link_libraries(tape_tests PRIVATE turing_core gtest )
add_test(NAME tape_tests COMMAND tape_tests)

add_executable(tm_tests ppois1_TuringMachine/MACHINELOGIC/machinelogicTest.cpp)
target_link_libraries(tm_tests PRIVATE turing_core gtest )
add_test(NAME tm_tests COMMAND tm_tests)