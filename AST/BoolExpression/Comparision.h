#pragma once

#include "../ASTNode.h"
#include "../ArithmeticExpression/ArithmeticExpression.h"

class Comparision : public BoolExpression {
   public:
    ArithmeticExpression* leftOperand;
    ArithmeticExpression* rightOperand;

    enum CompOp {
        LEQ, EQ
    };
    CompOp op;

    Comparision(size_t sourceLocation, ArithmeticExpression* leftOperand, ArithmeticExpression* rightOperand, CompOp op);
    ~Comparision() override;

    void visit(VisitorBase& v) override;
    bool evaluate(const State& state) const override;
};