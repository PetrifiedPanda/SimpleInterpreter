#pragma once

#include "../ASTNode.h"

class Sequence : public Statement {
   public:
    Statement* first;
    Statement* second;

    Sequence(size_t sourceLocation, Statement* first, Statement* second);
    ~Sequence() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};