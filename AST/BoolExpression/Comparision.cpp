#include "Comparision.h"

Comparision::Comparision(size_t sourceLocation, ArithmeticExpression* leftOperand, ArithmeticExpression* rightOperand, CompOp op) :
    BoolExpression(sourceLocation, COMP),
    leftOperand(leftOperand),
    rightOperand(rightOperand),
    op(op) {}
    
Comparision::~Comparision() {
    delete leftOperand;
    delete rightOperand;
}

void Comparision::visit(VisitorBase& v) {
    v.visitComp(this);
}

bool Comparision::evaluate(const State& state) const {
    int left = leftOperand->evaluate(state);
    int right = rightOperand->evaluate(state);

    switch (op) {
        case LEQ:
            return left <= right;
            
        case EQ:
            return left == right;
    }
    return false;
}