#pragma once

#include "../ASTNode.h"

class ABinaryOperation : public ArithmeticExpression {
   public:
    ArithmeticExpression* left_operand;
    ArithmeticExpression* right_operand;
    
    enum ArithOp {
        ADD, SUB, MUL, DIV
    };
    ArithOp op;

    ABinaryOperation(size_t source_location, ArithmeticExpression* left_operand, ArithmeticExpression* right_operand, ArithOp op);
    ~ABinaryOperation() override;

    void visit(VisitorBase& v) override;
    int evaluate(const State& state) const override;
};