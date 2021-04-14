#include "IfStatement.h"

IfStatement::IfStatement(size_t sourceLocation, BoolExpression* condition, Statement* ifCom, Statement* elseCom) :
        Statement(sourceLocation, IF),
        condition(condition),
        ifCom(ifCom),
        elseCom(elseCom) {}
    
IfStatement::~IfStatement() {
    delete condition;
    delete ifCom;
    delete elseCom;
}

void IfStatement::visit(VisitorBase& v) {
    v.visitIf(this);
}

void IfStatement::execute(State& state) const {
    bool cond = condition->evaluate(state);
    if (cond)
        ifCom->execute(state);
    else if (hasElse())
        elseCom->execute(state);
}

bool IfStatement::hasElse() const {
    return elseCom != nullptr;
}