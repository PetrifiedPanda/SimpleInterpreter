cmake_minimum_required(VERSION 3.10.2)

cmake_policy(SET CMP0076 NEW)

set(Sources 
    BBinaryOperation.cpp
    BoolLiteral.cpp
    Comparision.cpp
    Negation.cpp
)

target_sources(${This} PUBLIC ${Sources})