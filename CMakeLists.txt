cmake_minimum_required(VERSION 3.16)
project(EngRusDictionary CXX)

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
add_library(dict_core
    WORD/word.cpp
    ENTRY/entry.cpp
    DICTIONARY/dictionary.cpp
)
target_include_directories(dict_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# --- Консольная программа ---
add_executable(dict_main main.cpp)
target_link_libraries(dict_main PRIVATE dict_core)

# --- Тесты ---
add_executable(word_tests WORD/wordTest.cpp)
target_link_libraries(word_tests PRIVATE dict_core gtest)
add_test(NAME word_tests COMMAND word_tests)

add_executable(entry_tests ENTRY/entryTest.cpp)
target_link_libraries(entry_tests PRIVATE dict_core gtest)
add_test(NAME entry_tests COMMAND entry_tests)

add_executable(dictionary_tests DICTIONARY/dictionaryTest.cpp)
target_link_libraries(dictionary_tests PRIVATE dict_core gtest)
add_test(NAME dictionary_tests COMMAND dictionary_tests)