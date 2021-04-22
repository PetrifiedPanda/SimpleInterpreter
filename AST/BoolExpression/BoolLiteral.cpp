#include "BoolLiteral.h"

BoolLiteral::BoolLiteral(size_t source_location, bool value) :
        BoolExpression(source_location, LIT),
        value(value) {}

void BoolLiteral::visit(VisitorBase& v) {
    v.visit_bool_lit(this);
}

bool BoolLiteral::evaluate(const State& state) const {
    return value;
}