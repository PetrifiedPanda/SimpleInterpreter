#pragma once

#include <string>

#include "../ASTNode.h"
#include "../ArithmeticExpression/ArithmeticExpression.h"

class Assignment : public Statement {
   public:
    std::string varname;
    ArithmeticExpression* value_expression;

    Assignment(size_t source_location, std::string&& varname, ArithmeticExpression* value_expression); 
    ~Assignment() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};