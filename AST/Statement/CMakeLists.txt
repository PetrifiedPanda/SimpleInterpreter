cmake_minimum_required(VERSION 3.10.2)

cmake_policy(SET CMP0076 NEW)

set(Sources 
    Assignment.cpp
    IfStatement.cpp
    PrintStatement.cpp
    Sequence.cpp
    Skip.cpp
    WhileLoop.cpp
    ForLoop.cpp
    DoWhileLoop.cpp
)

target_sources(${This} PUBLIC ${Sources})