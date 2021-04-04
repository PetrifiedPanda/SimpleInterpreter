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
class NumericLiteral;
class VariableRef;

class BBinaryOperation;
class BoolLiteral;
class Comparision;
class Negation;

class VisitorBase {
   public:
    virtual void visitAssignment(Assignment* a) = 0;
    virtual void visitDoWhile(DoWhileLoop* l) = 0;
    virtual void visitForLoop(ForLoop* l) = 0;
    virtual void visitIf(IfStatement* i) = 0;
    virtual void visitPrint(PrintStatement* p) = 0;
    virtual void visitSequence(Sequence* s) = 0;
    virtual void visitSkip(Skip* s) = 0;
    virtual void visitWhile(WhileLoop* w) = 0;

    virtual void visitABinaryOp(ABinaryOperation* o) = 0;
    virtual void visitNumLit(NumericLiteral* l) = 0;
    virtual void visitVarRef(VariableRef* v) = 0;

    virtual void visitBBinaryOp(BBinaryOperation* o) = 0;
    virtual void visitBoolLit(BoolLiteral* l) = 0;
    virtual void visitComp(Comparision* c) = 0;
    virtual void visitNeg(Negation* n) = 0;

};

#include "AST.h"