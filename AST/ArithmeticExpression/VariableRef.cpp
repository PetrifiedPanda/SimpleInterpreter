#include "VariableRef.h"

VariableRef::VariableRef(size_t sourceLocation, std::string&& spelling) :
        ArithmeticExpression(sourceLocation, VAR),
        spelling(std::move(spelling)) {}

void VariableRef::visit(VisitorBase& v) {
    v.visitVarRef(this);
}

int VariableRef::evaluate(const State& state) const {
    return state.readVariable(spelling);
}