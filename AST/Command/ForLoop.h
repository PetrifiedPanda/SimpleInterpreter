#pragma once

#include "../ASTNode.h"
#include "../BoolExpression/BoolExpression.h"

class ForLoop : public Command {
   public:
    Command* initExpr;
    BoolExpression* condition;
    Command* incrExpression;
    Command* loopBody;

    ForLoop(size_t sourceLocation, Command* initCommand, BoolExpression* condition, Command* incrExpression, Command* loopBody);
    ~ForLoop() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};