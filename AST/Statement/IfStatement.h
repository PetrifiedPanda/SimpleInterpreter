#pragma once

#include "../ASTNode.h"
#include "../BoolExpression/BoolExpression.h"

class IfStatement : public Statement {
   public:
    BoolExpression* condition;
    Statement* ifCom;
    Statement* elseCom;

    IfStatement(size_t sourceLocation, BoolExpression* condition, Statement* ifCom, Statement* elseCom);
    ~IfStatement() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;

    bool hasElse() const;
};