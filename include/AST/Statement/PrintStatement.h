#pragma once

#include <iostream>

#include "../ASTNode.h"
#include "../ArithmeticExpression/ArithmeticExpression.h"

class PrintStatement : public Statement {
   public:
    ArithmeticExpression* to_print;

    PrintStatement(size_t source_location, ArithmeticExpression* to_print);
    ~PrintStatement() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};