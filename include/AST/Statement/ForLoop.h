#pragma once

#include "../ASTNode.h"
#include "../BoolExpression/BoolExpression.h"

class ForLoop : public Statement {
   public:
    Statement* init_expr;
    BoolExpression* condition;
    Statement* incr_expr;
    Statement* loop_body;

    ForLoop(size_t source_location, Statement* init_expr, BoolExpression* condition, Statement* incr_expr, Statement* loop_body);
    ~ForLoop() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};