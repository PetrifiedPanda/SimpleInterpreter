#pragma once

#include "../ASTNode.h"
#include "../BoolExpression/BoolExpression.h"

class DoWhileLoop : public Statement {
  public:
    BoolExpression* condition;
    Statement* loopBody;

    DoWhileLoop(size_t sourceLocation, BoolExpression* condition, Statement* loopBody);
    ~DoWhileLoop() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};