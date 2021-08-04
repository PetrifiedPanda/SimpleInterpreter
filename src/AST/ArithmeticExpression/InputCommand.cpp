#include "AST/ArithmeticExpression/InputCommand.h"

#include <iostream>

InputCommand::InputCommand(size_t source_location) : ArithmeticExpression{source_location, INPUT} {}

void InputCommand::visit(VisitorBase& v) {
    v.visit_input(this);
}

int InputCommand::evaluate(const State& state) const {
    int x;
    std::cin >> x;
    return x;
}