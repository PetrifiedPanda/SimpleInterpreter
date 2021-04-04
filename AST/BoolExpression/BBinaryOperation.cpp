#include "BBinaryOperation.h"

BBinaryOperation::BBinaryOperation(size_t sourceLocation, BoolExpression* leftOperand, BoolExpression* rightOperand, LogOp op) :
    BoolExpression(sourceLocation, BINOP),
    leftOperand(leftOperand),
    rightOperand(rightOperand),
    op(op) {}
    
BBinaryOperation::~BBinaryOperation() {
    delete leftOperand;
    delete rightOperand;
}

void BBinaryOperation::visit(VisitorBase& v) {
    v.visitBBinaryOp(this);
}

bool BBinaryOperation::evaluate(const State& state) const {
    bool left = leftOperand->evaluate(state);
    bool right = rightOperand->evaluate(state);

    switch (op) {
        case AND:
            return left && right;
            
        case OR:
            return left || right;
    }
    return false;
}