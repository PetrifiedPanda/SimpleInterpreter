#include "AST/BoolExpression/BBinaryOperation.h"

BBinaryOperation::BBinaryOperation(size_t source_location, BoolExpression* left_operand, BoolExpression* right_operand, LogOp op) :
    BoolExpression{source_location, BINOP},
    left_operand{left_operand},
    right_operand{right_operand},
    op{op} {}
    
BBinaryOperation::~BBinaryOperation() {
    delete left_operand;
    delete right_operand;
}

void BBinaryOperation::visit(VisitorBase& v) {
    v.visit_b_binary_op(this);
}

bool BBinaryOperation::evaluate(const State& state) const {
    bool left = left_operand->evaluate(state);
    bool right = right_operand->evaluate(state);

    switch (op) {
        case AND:
            return left && right;
            
        case OR:
            return left || right;
    }
    return false;
}