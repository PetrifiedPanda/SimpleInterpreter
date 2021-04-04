#pragma once

#include "../State.h"
#include "../ASTNode.h"

class ArithmeticExpression : public ASTNode {
   public:
    enum Type {
        BINOP, LIT, VAR
    };

    const Type type;
    ArithmeticExpression(size_t sourceLocation, Type type) : ASTNode(sourceLocation), type(type) {}

    virtual int evaluate(const State& state) const = 0;
};