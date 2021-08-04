#pragma once

#include "../ASTNode.h"
#include "../BoolExpression/BoolExpression.h"

class WhileLoop : public Statement {
  public:
    BoolExpression* condition;
    Statement* loop_body;

    WhileLoop(size_t source_location, BoolExpression* condition, Statement* loop_body);
    ~WhileLoop() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};