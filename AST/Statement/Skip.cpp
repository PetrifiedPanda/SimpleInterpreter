#include "Skip.h"

Skip::Skip(size_t source_location) :
    Statement(source_location, SKIP) {}

void Skip::visit(VisitorBase& v) {
    v.visit_skip(this);
}

void Skip::execute(State& state) const {}