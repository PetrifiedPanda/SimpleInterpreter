#pragma once

#include "../ASTNode.h"

class Sequence : public Command {
   public:
    Command* first;
    Command* second;

    Sequence(size_t sourceLocation, Command* first, Command* second);
    ~Sequence() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};