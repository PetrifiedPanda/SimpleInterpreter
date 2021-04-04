#include "PrintStatement.h"

PrintStatement::PrintStatement(size_t sourceLocation, ArithmeticExpression* toPrint) :
        Command(sourceLocation, PRINT),
        toPrint(toPrint) {}
    
PrintStatement::~PrintStatement() {
    delete toPrint;
}

void PrintStatement::visit(VisitorBase& v) {
    v.visitPrint(this);
}

void PrintStatement::execute(State& state) const {
    int val = toPrint->evaluate(state);
    std::cout << val << std::endl;
}