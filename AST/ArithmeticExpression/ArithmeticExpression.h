#pragma once

#include "../State.h"
#include "../ASTNode.h"

class ArithmeticExpression : public ASTNode {
   public:
    enum Type {
        BINOP, LIT, VAR, INPUT
    };

    const Type type;
    ArithmeticExpression(size_t source_location, Type type) : ASTNode(source_location), type(type) {}

    virtual int evaluate(const State& state) const = 0;
};