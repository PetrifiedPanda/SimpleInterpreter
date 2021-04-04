#pragma once

#include "../ASTNode.h"
#include "../BoolExpression/BoolExpression.h"

class IfStatement : public Command {
   public:
    BoolExpression* condition;
    Command* ifCom;
    Command* elseCom;

    IfStatement(size_t sourceLocation, BoolExpression* condition, Command* ifCom, Command* elseCom);
    ~IfStatement() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;

    bool hasElse() const;
};