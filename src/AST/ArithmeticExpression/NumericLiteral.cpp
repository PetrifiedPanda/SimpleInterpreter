#include "AST/ArithmeticExpression/NumericLiteral.h"

NumericLiteral::NumericLiteral(size_t source_location, int value) :
        ArithmeticExpression(source_location, LIT),
        value(value) {}

void NumericLiteral::visit(VisitorBase& v) {
    v.visit_num_lit(this);
}

int NumericLiteral::evaluate(const State& state) const {
    return value;
}