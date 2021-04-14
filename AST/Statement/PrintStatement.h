#pragma once

#include <iostream>

#include "../ASTNode.h"
#include "../ArithmeticExpression/ArithmeticExpression.h"

class PrintStatement : public Statement {
   public:
    ArithmeticExpression* toPrint;

    PrintStatement(size_t sourceLocation, ArithmeticExpression* toPrint);
    ~PrintStatement() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};