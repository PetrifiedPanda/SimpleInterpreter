#include "AST/BoolExpression/Comparision.h"

Comparision::Comparision(size_t source_location, ArithmeticExpression* left_operand, ArithmeticExpression* right_operand, CompOp op) :
    BoolExpression{source_location, COMP},
    left_operand{left_operand},
    right_operand{right_operand},
    op{op} {}
    
Comparision::~Comparision() {
    delete left_operand;
    delete right_operand;
}

void Comparision::visit(VisitorBase& v) {
    v.visit_comp(this);
}

bool Comparision::evaluate(const State& state) const {
    int left = left_operand->evaluate(state);
    int right = right_operand->evaluate(state);

    switch (op) {
        case EQ:
            return left == right;

        case NEQ:
            return left != right;

        case LEQ:
            return left <= right;
        
        case LT:
            return left < right;
        
        case GEQ:
            return left >= right;
        
        case GT:
            return left > right;
    }
    return false;
}