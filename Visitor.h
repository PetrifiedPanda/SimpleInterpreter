#pragma once

#include <list>
#include <string>

#include "AST/VisitorBase.h"

class Visitor : public VisitorBase {
    const std::string& command_;
    std::list<std::list<std::string>> identifiers_;
    const State& state_;

   public:
    Visitor(const std::string& command, const State& state);

    void clear();

    void visitAssignment(Assignment* a) override;
    void visitDoWhile(DoWhileLoop* l) override;
    void visitForLoop(ForLoop* l) override;
    void visitIf(IfStatement* i) override;
    void visitPrint(PrintStatement* p) override;
    void visitSequence(Sequence* s) override;
    void visitSkip(Skip* s) override;
    void visitWhile(WhileLoop* w) override;

    void visitABinaryOp(ABinaryOperation* o) override;
    void visitNumLit(NumericLiteral* l) override;
    void visitVarRef(VariableRef* v) override;

    void visitBBinaryOp(BBinaryOperation* o) override;
    void visitBoolLit(BoolLiteral* l) override;
    void visitComp(Comparision* c) override;
    void visitNeg(Negation* n) override;

   private:
    void addIdentifier(const std::string& varname);

    bool contains(const std::string& varname) const;

    void scopeUnion(Command* first, Command* second);
};