#pragma once

#include "../ASTNode.h"
#include "../BoolExpression/BoolExpression.h"

class DoWhileLoop : public Command {
  public:
    BoolExpression* condition;
    Command* loopBody;

    DoWhileLoop(size_t sourceLocation, BoolExpression* condition, Command* loopBody);
    ~DoWhileLoop() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};