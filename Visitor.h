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

    void visit_assignment(Assignment* a) override;
    void visit_do_while(DoWhileLoop* l) override;
    void visit_for_loop(ForLoop* l) override;
    void visit_if(IfStatement* i) override;
    void visit_print(PrintStatement* p) override;
    void visit_sequence(Sequence* s) override;
    void visit_skip(Skip* s) override;
    void visit_while(WhileLoop* w) override;

    void visit_a_binary_op(ABinaryOperation* o) override;
    void visit_input(InputCommand* i) override;
    void visit_num_lit(NumericLiteral* l) override;
    void visit_var_ref(VariableRef* v) override;

    void visit_b_binary_op(BBinaryOperation* o) override;
    void visit_bool_lit(BoolLiteral* l) override;
    void visit_comp(Comparision* c) override;
    void visit_neg(Negation* n) override;

   private:
    void addIdentifier(const std::string& varname);

    bool contains(const std::string& varname) const;

    void scopeUnion(Statement* first, Statement* second);
};