#pragma once

#include "../ASTNode.h"

class BBinaryOperation : public BoolExpression {
   public:
    BoolExpression* left_operand;
    BoolExpression* right_operand;

    enum LogOp {
        AND, OR
    };
    LogOp op;
    
    BBinaryOperation(size_t source_location, BoolExpression* left_operand, BoolExpression* right_operand, LogOp op);
    ~BBinaryOperation() override;

    void visit(VisitorBase& v) override;
    bool evaluate(const State& state) const override;
};