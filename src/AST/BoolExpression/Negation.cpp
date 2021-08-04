#include "AST/BoolExpression/Negation.h"

Negation::Negation(size_t source_location, BoolExpression* expr) :
    BoolExpression{source_location, NEG},
    expr{expr} {}

Negation::~Negation() {
    delete expr;
}

void Negation::visit(VisitorBase& v) {
    v.visit_neg(this);
}

bool Negation::evaluate(const State& state) const {
    return !expr->evaluate(state);
}