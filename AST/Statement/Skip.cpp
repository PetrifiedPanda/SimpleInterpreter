#include "Skip.h"

Skip::Skip(size_t sourceLocation) :
    Statement(sourceLocation, SKIP) {}

void Skip::visit(VisitorBase& v) {
    v.visitSkip(this);
}

void Skip::execute(State& state) const {}