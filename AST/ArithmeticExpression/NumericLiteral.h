#pragma once

#include "../ASTNode.h"

class NumericLiteral : public ArithmeticExpression {
   public:
    const int value;

    NumericLiteral(size_t sourceLocation, int value);

    void visit(VisitorBase& v) override;
    int evaluate(const State& state) const override;
};