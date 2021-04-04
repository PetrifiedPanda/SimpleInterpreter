#include "DoWhileLoop.h"

DoWhileLoop::DoWhileLoop(size_t sourceLocation, BoolExpression* condition, Command* loopBody) :
    Command(sourceLocation, DOWHILE),
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