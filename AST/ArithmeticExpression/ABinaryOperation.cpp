#include "ABinaryOperation.h"

ABinaryOperation::ABinaryOperation(size_t sourceLocation, ArithmeticExpression* leftOperand, ArithmeticExpression* rightOperand, ArithOp op) :
    ArithmeticExpression(sourceLocation, BINOP),
    leftOperand(leftOperand),
    rightOperand(rightOperand),
    op(op) {}
    
ABinaryOperation::~ABinaryOperation() {
    delete leftOperand;
    delete rightOperand;
}

void ABinaryOperation::visit(VisitorBase& v) {
    v.visitABinaryOp(this);
}

int ABinaryOperation::evaluate(const State& state) const {
    int left = leftOperand->evaluate(state);
    int right = rightOperand->evaluate(state);

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