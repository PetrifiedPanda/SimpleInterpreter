#pragma once

#include "../ASTNode.h"

class Negation : public BoolExpression {
   public:
    BoolExpression* expr;

    Negation(size_t sourceLocation, BoolExpression* expr);
    ~Negation() override;

    void visit(VisitorBase& v) override;
    bool evaluate(const State& state) const override;
};