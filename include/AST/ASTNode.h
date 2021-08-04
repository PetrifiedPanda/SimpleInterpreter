#pragma once

#include <cstddef>

class VisitorBase;

class ASTNode {
   public:
    const size_t source_location;

    ASTNode(size_t source_location) : source_location(source_location) {}
    virtual ~ASTNode() {}

    virtual void visit(VisitorBase& v) = 0;
};

#include "VisitorBase.h"