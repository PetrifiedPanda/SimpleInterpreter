#pragma once

#include "../ASTNode.h"

class InputCommand : public ArithmeticExpression {
   public:
    InputCommand(size_t sourceLocation);

    void visit(VisitorBase& v) override;
    int evaluate(const State& state) const override;
};