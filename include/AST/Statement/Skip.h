#pragma once

#include "../ASTNode.h"

class Skip : public Statement {
   public:
    Skip(size_t source_location);

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};