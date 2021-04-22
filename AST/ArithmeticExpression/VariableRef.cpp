#include "VariableRef.h"

VariableRef::VariableRef(size_t source_location, std::string&& spelling) :
        ArithmeticExpression(source_location, VAR),
        spelling(std::move(spelling)) {}

void VariableRef::visit(VisitorBase& v) {
    v.visit_var_ref(this);
}

int VariableRef::evaluate(const State& state) const {
    return state.read_variable(spelling);
}