cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

set(This Interpreter)

project(${This} LANGUAGES CXX)

set(Sources
    Main.cpp
    Tokenizer.cpp
    Parser.cpp
    Visitor.cpp
)


add_executable(${This} ${Sources})

add_subdirectory(AST)
add_subdirectory(Error)
