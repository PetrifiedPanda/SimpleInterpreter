cmake_minimum_required(VERSION 3.10.2)

cmake_policy(SET CMP0076 NEW)

set(Sources 
    State.cpp
)

target_sources(${This} PUBLIC ${Sources})

add_subdirectory(Statement)
add_subdirectory(ArithmeticExpression)
add_subdirectory(BoolExpression)