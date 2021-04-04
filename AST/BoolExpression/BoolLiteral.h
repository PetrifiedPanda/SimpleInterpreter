#pragma once

#include "../ASTNode.h"

class BoolLiteral : public BoolExpression {
    bool value;

   public:
    BoolLiteral(size_t sourceLocation, bool value);

    void visit(VisitorBase& v) override;

    bool evaluate(const State& state) const override;
};