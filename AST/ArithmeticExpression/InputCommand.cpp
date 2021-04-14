#include "InputCommand.h"

#include <iostream>

InputCommand::InputCommand(size_t sourceLocation) : ArithmeticExpression(sourceLocation, INPUT) {}

void InputCommand::visit(VisitorBase& v) {
    v.visitInput(this);
}

int InputCommand::evaluate(const State& state) const {
    int x;
    std::cin >> x;
    return x;
}