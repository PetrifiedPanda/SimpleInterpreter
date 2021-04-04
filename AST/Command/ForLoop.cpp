#include "ForLoop.h"

ForLoop::ForLoop(size_t sourceLocation, Command* initCommand, BoolExpression* condition, Command* incrExpression, Command* loopBody) :
    Command(sourceLocation, FOR),
    initExpr(initCommand),
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