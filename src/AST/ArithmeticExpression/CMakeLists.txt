cmake_minimum_required(VERSION 3.10.2)

cmake_policy(SET CMP0076 NEW)

set(Sources 
    ABinaryOperation.cpp
    InputCommand.cpp
    NumericLiteral.cpp
    VariableRef.cpp
)

target_sources(${This} PUBLIC ${Sources})