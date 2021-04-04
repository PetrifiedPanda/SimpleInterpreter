#pragma once

#include <cstddef>

class VisitorBase;

class ASTNode {
   public:
    const size_t sourceLocation;

    ASTNode(size_t sourceLocation) : sourceLocation(sourceLocation) {}
    virtual ~ASTNode() {}

    virtual void visit(VisitorBase& v) = 0;
};

#include "VisitorBase.h"