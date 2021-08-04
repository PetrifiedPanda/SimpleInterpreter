#include "AST/Statement/WhileLoop.h"

WhileLoop::WhileLoop(size_t source_location, BoolExpression* condition, Statement* loop_body) :
    Statement(source_location, WHILE),
    condition(condition),
    loop_body(loop_body) {}

WhileLoop::~WhileLoop() {
    delete condition;
    delete loop_body;
} 

void WhileLoop::visit(VisitorBase& v) {
    v.visit_while(this);
}

void WhileLoop::execute(State& state) const {
    bool cond = condition->evaluate(state);
    while (cond) {
        loop_body->execute(state);
        cond = condition->evaluate(state);
    }
}