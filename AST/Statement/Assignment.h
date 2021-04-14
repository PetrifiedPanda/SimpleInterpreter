#pragma once

#include <string>

#include "../ASTNode.h"
#include "../ArithmeticExpression/ArithmeticExpression.h"

class Assignment : public Statement {
   public:
    std::string varname;
    ArithmeticExpression* valueExpression;

    Assignment(size_t sourceLocation, std::string&& varname, ArithmeticExpression* valueExpression); 
    ~Assignment() override;

    void visit(VisitorBase& v) override;
    void execute(State& state) const override;
};