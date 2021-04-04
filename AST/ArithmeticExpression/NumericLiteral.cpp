#include "NumericLiteral.h"

NumericLiteral::NumericLiteral(size_t sourceLocation, int value) :
        ArithmeticExpression(sourceLocation, LIT),
        value(value) {}

void NumericLiteral::visit(VisitorBase& v) {
    v.visitNumLit(this);
}

int NumericLiteral::evaluate(const State& state) const {
    return value;
}