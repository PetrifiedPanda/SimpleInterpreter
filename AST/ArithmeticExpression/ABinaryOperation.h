#pragma once

#include "../ASTNode.h"

class ABinaryOperation : public ArithmeticExpression {
   public:
    ArithmeticExpression* leftOperand;
    ArithmeticExpression* rightOperand;
    
    enum ArithOp {
        ADD, SUB, MUL, DIV
    };
    ArithOp op;

    ABinaryOperation(size_t sourceLocation, ArithmeticExpression* leftOperand, ArithmeticExpression* rightOperand, ArithOp op);
    ~ABinaryOperation() override;

    void visit(VisitorBase& v) override;
    int evaluate(const State& state) const override;
};