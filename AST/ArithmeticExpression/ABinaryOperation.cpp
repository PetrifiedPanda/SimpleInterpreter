#include "ABinaryOperation.h"

ABinaryOperation::ABinaryOperation(size_t source_location, ArithmeticExpression* left_operand, ArithmeticExpression* right_operand, ArithOp op) :
    ArithmeticExpression(source_location, BINOP),
    left_operand(left_operand),
    right_operand(right_operand),
    op(op) {}
    
ABinaryOperation::~ABinaryOperation() {
    delete left_operand;
    delete right_operand;
}

void ABinaryOperation::visit(VisitorBase& v) {
    v.visit_a_binary_op(this);
}

int ABinaryOperation::evaluate(const State& state) const {
    int left = left_operand->evaluate(state);
    int right = right_operand->evaluate(state);

    switch (op) {
        case ADD:
            return left + right;
            
        case SUB:
            return left - right;
            
        case MUL:
            return left * right;

        case DIV:
            return left / right;
    }
    return 0;
}