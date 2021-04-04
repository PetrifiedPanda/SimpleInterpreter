#pragma once

#include "../ASTNode.h"
#include "../BoolExpression/BoolExpression.h"

class WhileLoop : public Command {
  public:
    BoolExpression* condition;
    Command* loopBody;

    WhileLoop(size_t sourceLocation, BoolExpression* condition, Command* loopBody);
    ~WhileLoop() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};