#include "Assignment.h"

Assignment::Assignment(size_t sourceLocation, std::string&& varname, ArithmeticExpression* valueExpression) : 
        Command(sourceLocation, ASSIGN), 
        varname(std::move(varname)), 
        valueExpression(valueExpression) {}

Assignment::~Assignment() {
    delete valueExpression;
}

void Assignment::visit(VisitorBase& v) {
    v.visitAssignment(this);
}

void Assignment::execute(State& state) const {
    int value = valueExpression->evaluate(state);
    state.writeVariable(varname, value);
}