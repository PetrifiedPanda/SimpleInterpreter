#include "Negation.h"

Negation::Negation(size_t sourceLocation, BoolExpression* expr) :
    BoolExpression(sourceLocation, NEG),
    expr(expr) {}

Negation::~Negation() {
    delete expr;
}

void Negation::visit(VisitorBase& v) {
    v.visitNeg(this);
}

bool Negation::evaluate(const State& state) const {
    return !expr->evaluate(state);
}