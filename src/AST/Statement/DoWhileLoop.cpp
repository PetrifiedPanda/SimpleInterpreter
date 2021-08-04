#include "AST/Statement/DoWhileLoop.h"

DoWhileLoop::DoWhileLoop(size_t source_location, BoolExpression* condition, Statement* loop_body) :
    Statement{source_location, DOWHILE},
    condition{condition},
    loop_body{loop_body} {}

DoWhileLoop::~DoWhileLoop() {
    delete condition;
    delete loop_body;
} 

void DoWhileLoop::visit(VisitorBase& v) {
    v.visit_do_while(this);
}

void DoWhileLoop::execute(State& state) const {
    loop_body->execute(state);
    bool cond = condition->evaluate(state);
    while (cond) {
        loop_body->execute(state);
        cond = condition->evaluate(state);
    }
}