#pragma once

#include "../ASTNode.h"

class Skip : public Command {
   public:
    Skip(size_t sourceLocation);

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};