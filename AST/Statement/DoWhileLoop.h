#pragma once

#include "../ASTNode.h"
#include "../BoolExpression/BoolExpression.h"

class DoWhileLoop : public Statement {
  public:
    BoolExpression* condition;
    Statement* loop_body;

    DoWhileLoop(size_t source_location, BoolExpression* condition, Statement* loop_body);
    ~DoWhileLoop() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};