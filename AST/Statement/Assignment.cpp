#include "Assignment.h"

Assignment::Assignment(size_t source_location, std::string&& varname, ArithmeticExpression* value_expression) : 
        Statement(source_location, ASSIGN), 
        varname(std::move(varname)), 
        value_expression(value_expression) {}

Assignment::~Assignment() {
    delete value_expression;
}

void Assignment::visit(VisitorBase& v) {
    v.visit_assignment(this);
}

void Assignment::execute(State& state) const {
    int value = value_expression->evaluate(state);
    state.write_variable(varname, value);
}