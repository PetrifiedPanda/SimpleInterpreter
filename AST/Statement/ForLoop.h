#pragma once

#include "../ASTNode.h"
#include "../BoolExpression/BoolExpression.h"

class ForLoop : public Statement {
   public:
    Statement* initExpr;
    BoolExpression* condition;
    Statement* incrExpression;
    Statement* loopBody;

    ForLoop(size_t sourceLocation, Statement* initStatement, BoolExpression* condition, Statement* incrExpression, Statement* loopBody);
    ~ForLoop() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};