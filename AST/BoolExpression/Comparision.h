#pragma once

#include "../ASTNode.h"
#include "../ArithmeticExpression/ArithmeticExpression.h"

class Comparision : public BoolExpression {
   public:
    ArithmeticExpression* left_operand;
    ArithmeticExpression* right_operand;

    enum CompOp {
        LEQ, EQ
    };
    CompOp op;

    Comparision(size_t source_location, ArithmeticExpression* left_operand, ArithmeticExpression* right_operand, CompOp op);
    ~Comparision() override;

    void visit(VisitorBase& v) override;
    bool evaluate(const State& state) const override;
};