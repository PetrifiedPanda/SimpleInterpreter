#include "Sequence.h"

Sequence::Sequence(size_t sourceLocation, Statement* first, Statement* second) :
    Statement(sourceLocation, SEQ),
    first(first),
    second(second) {}

Sequence::~Sequence() {
    delete first;
    delete second;
}

void Sequence::visit(VisitorBase& v) {
    v.visitSequence(this);
}

void Sequence::execute(State& state) const {
    first->execute(state);
    second->execute(state);
}