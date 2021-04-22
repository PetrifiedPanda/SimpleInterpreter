#include "IfStatement.h"

IfStatement::IfStatement(size_t source_location, BoolExpression* condition, Statement* if_com, Statement* else_com) :
        Statement(source_location, IF),
        condition(condition),
        if_com(if_com),
        else_com(else_com) {}
    
IfStatement::~IfStatement() {
    delete condition;
    delete if_com;
    delete else_com;
}

void IfStatement::visit(VisitorBase& v) {
    v.visit_if(this);
}

void IfStatement::execute(State& state) const {
    bool cond = condition->evaluate(state);
    if (cond)
        if_com->execute(state);
    else if (has_else())
        else_com->execute(state);
}

bool IfStatement::has_else() const {
    return else_com != nullptr;
}