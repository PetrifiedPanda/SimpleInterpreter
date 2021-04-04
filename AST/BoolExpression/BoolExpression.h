#pragma once

#include "../State.h"
#include "../ASTNode.h"

class BoolExpression : public ASTNode {
   public:
    enum Type {
        BINOP, LIT, COMP, NEG
    };
    
    const Type type;
    BoolExpression(size_t sourceLocation, Type type) : ASTNode(sourceLocation), type(type) {}

    virtual bool evaluate(const State& state) const = 0;
};