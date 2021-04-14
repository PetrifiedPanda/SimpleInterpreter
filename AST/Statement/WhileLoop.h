#pragma once

#include "../ASTNode.h"
#include "../BoolExpression/BoolExpression.h"

class WhileLoop : public Statement {
  public:
    BoolExpression* condition;
    Statement* loopBody;

    WhileLoop(size_t sourceLocation, BoolExpression* condition, Statement* loopBody);
    ~WhileLoop() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};