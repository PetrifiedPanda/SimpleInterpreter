#include "AST/Statement/Sequence.h"

Sequence::Sequence(size_t source_location, Statement* first, Statement* second) :
    Statement{source_location, SEQ},
    first{first},
    second{second} {}

Sequence::~Sequence() {
    delete first;
    delete second;
}

void Sequence::visit(VisitorBase& v) {
    v.visit_sequence(this);
}

void Sequence::execute(State& state) const {
    first->execute(state);
    second->execute(state);
}