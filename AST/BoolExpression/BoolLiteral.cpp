#include "BoolLiteral.h"

BoolLiteral::BoolLiteral(size_t sourceLocation, bool value) :
        BoolExpression(sourceLocation, LIT),
        value(value) {}

void BoolLiteral::visit(VisitorBase& v) {
    v.visitBoolLit(this);
}

bool BoolLiteral::evaluate(const State& state) const {
    return value;
}