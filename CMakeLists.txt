cmake_minimum_required(VERSION 3.15)

project(abstract)

add_executable(abstract_tests tests.cpp main.cpp)

target_link_libraries(abstract_tests)

set_target_properties(abstract_tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_CLANG_TIDY clang-tidy
)

