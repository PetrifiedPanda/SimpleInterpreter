#pragma once

#include "../State.h"
#include "../ASTNode.h"

class Statement : public ASTNode {
   public:
    enum Type {
        ASSIGN, FOR, IF, PRINT, SEQ, SKIP, WHILE, DOWHILE
    };

    const Type type;
    Statement(size_t sourceLocation, Type type) : ASTNode(sourceLocation), type(type) {}

    virtual void execute(State& state) const = 0;
};