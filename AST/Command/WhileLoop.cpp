#include "WhileLoop.h"

WhileLoop::WhileLoop(size_t sourceLocation, BoolExpression* condition, Command* loopBody) :
    Command(sourceLocation, WHILE),
    condition(condition),
    loopBody(loopBody) {}

WhileLoop::~WhileLoop() {
    delete condition;
    delete loopBody;
} 

void WhileLoop::visit(VisitorBase& v) {
    v.visitWhile(this);
}

void WhileLoop::execute(State& state) const {
    bool cond = condition->evaluate(state);
    while (cond) {
        loopBody->execute(state);
        cond = condition->evaluate(state);
    }
}