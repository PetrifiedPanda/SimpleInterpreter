cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

set(This Interpreter)

project(${This} LANGUAGES CXX)

set(Sources
    Main.cpp
    src/Tokenizer.cpp
    src/Parser.cpp
    src/Visitor.cpp
)


add_executable(${This} ${Sources})

target_include_directories(${This} PRIVATE ./include)

add_subdirectory(src/AST)
add_subdirectory(src/Error)
