#include "ForLoop.h"

ForLoop::ForLoop(size_t source_location, Statement* initStatement, BoolExpression* condition, Statement* incr_expr, Statement* loop_body) :
    Statement(source_location, FOR),
    init_expr(initStatement),
    condition(condition),
    incr_expr(incr_expr),
    loop_body(loop_body) {}

ForLoop::~ForLoop() {
    delete init_expr;
    delete condition;
    delete incr_expr;
    delete loop_body;
}

void ForLoop::visit(VisitorBase& v) {
    v.visit_for_loop(this);
}

void ForLoop::execute(State& state) const {
    init_expr->execute(state);

    while (condition->evaluate(state)) {
        loop_body->execute(state);
        incr_expr->execute(state);
    }
}