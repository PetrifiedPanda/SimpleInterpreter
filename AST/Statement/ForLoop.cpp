#include "ForLoop.h"

ForLoop::ForLoop(size_t sourceLocation, Statement* initStatement, BoolExpression* condition, Statement* incrExpression, Statement* loopBody) :
    Statement(sourceLocation, FOR),
    initExpr(initStatement),
    condition(condition),
    incrExpression(incrExpression),
    loopBody(loopBody) {}

ForLoop::~ForLoop() {
    delete initExpr;
    delete condition;
    delete incrExpression;
    delete loopBody;
}

void ForLoop::visit(VisitorBase& v) {
    v.visitForLoop(this);
}

void ForLoop::execute(State& state) const {
    initExpr->execute(state);

    while (condition->evaluate(state)) {
        loopBody->execute(state);
        incrExpression->execute(state);
    }
}