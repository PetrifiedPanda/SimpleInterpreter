#pragma once

class Assignment;
class DoWhileLoop;
class ForLoop;
class IfStatement;
class PrintStatement;
class Sequence;
class Skip;
class WhileLoop;

class ABinaryOperation;
class InputCommand;
class NumericLiteral;
class VariableRef;

class BBinaryOperation;
class BoolLiteral;
class Comparision;
class Negation;

class VisitorBase {
   public:
    virtual void visit_assignment(Assignment* a) = 0;
    virtual void visit_do_while(DoWhileLoop* l) = 0;
    virtual void visit_for_loop(ForLoop* l) = 0;
    virtual void visit_if(IfStatement* i) = 0;
    virtual void visit_print(PrintStatement* p) = 0;
    virtual void visit_sequence(Sequence* s) = 0;
    virtual void visit_skip(Skip* s) = 0;
    virtual void visit_while(WhileLoop* w) = 0;

    virtual void visit_a_binary_op(ABinaryOperation* o) = 0;
    virtual void visit_input(InputCommand* i) = 0;
    virtual void visit_num_lit(NumericLiteral* l) = 0;
    virtual void visit_var_ref(VariableRef* v) = 0;

    virtual void visit_b_binary_op(BBinaryOperation* o) = 0;
    virtual void visit_bool_lit(BoolLiteral* l) = 0;
    virtual void visit_comp(Comparision* c) = 0;
    virtual void visit_neg(Negation* n) = 0;

};

#include "AST.h"