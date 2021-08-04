#pragma once

#include "../ASTNode.h"

class Sequence : public Statement {
   public:
    Statement* first;
    Statement* second;

    Sequence(size_t source_location, Statement* first, Statement* second);
    ~Sequence() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};