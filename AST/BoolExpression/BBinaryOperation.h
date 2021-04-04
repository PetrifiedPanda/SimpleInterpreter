#pragma once

#include "../ASTNode.h"

class BBinaryOperation : public BoolExpression {
   public:
    BoolExpression* leftOperand;
    BoolExpression* rightOperand;

    enum LogOp {
        AND, OR
    };
    LogOp op;
    
    BBinaryOperation(size_t sourceLocation, BoolExpression* leftOperand, BoolExpression* rightOperand, LogOp op);
    ~BBinaryOperation() override;

    void visit(VisitorBase& v) override;
    bool evaluate(const State& state) const override;
};