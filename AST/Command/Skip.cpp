#include "Skip.h"

Skip::Skip(size_t sourceLocation) :
    Command(sourceLocation, SKIP) {}

void Skip::visit(VisitorBase& v) {
    v.visitSkip(this);
}

void Skip::execute(State& state) const {}