#include "DoWhileLoop.h"

DoWhileLoop::DoWhileLoop(size_t sourceLocation, BoolExpression* condition, Statement* loopBody) :
    Statement(sourceLocation, DOWHILE),
    condition(condition),
    loopBody(loopBody) {}

DoWhileLoop::~DoWhileLoop() {
    delete condition;
    delete loopBody;
} 

void DoWhileLoop::visit(VisitorBase& v) {
    v.visitDoWhile(this);
}

void DoWhileLoop::execute(State& state) const {
    loopBody->execute(state);
    bool cond = condition->evaluate(state);
    while (cond) {
        loopBody->execute(state);
        cond = condition->evaluate(state);
    }
}