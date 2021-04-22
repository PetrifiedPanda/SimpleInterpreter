#pragma once

#include <string>

#include "../ASTNode.h"

class VariableRef : public ArithmeticExpression {
   public:
    const std::string spelling;

    VariableRef(size_t source_location, std::string&& spelling);

    void visit(VisitorBase& v) override;
    int evaluate(const State& state) const override;
};