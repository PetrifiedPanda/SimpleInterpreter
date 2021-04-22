#include "PrintStatement.h"

PrintStatement::PrintStatement(size_t source_location, ArithmeticExpression* to_print) :
        Statement(source_location, PRINT),
        to_print(to_print) {}
    
PrintStatement::~PrintStatement() {
    delete to_print;
}

void PrintStatement::visit(VisitorBase& v) {
    v.visit_print(this);
}

void PrintStatement::execute(State& state) const {
    int val = to_print->evaluate(state);
    std::cout << val << std::endl;
}