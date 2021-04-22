#pragma once

#include "../ASTNode.h"
#include "../BoolExpression/BoolExpression.h"

class IfStatement : public Statement {
   public:
    BoolExpression* condition;
    Statement* if_com;
    Statement* else_com;

    IfStatement(size_t source_location, BoolExpression* condition, Statement* if_com, Statement* else_com);
    ~IfStatement() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;

    bool has_else() const;
};