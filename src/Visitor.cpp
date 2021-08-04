#include "Visitor.h"

#include <stdexcept>

#include "Error/InterpreterError.h"

Visitor::Visitor(const std::string& command, const State& state) : command_{command}, identifiers_{}, state_{state} {
    identifiers_.emplace_front();
}

void Visitor::visit_assignment(Assignment* a) {
    a->value_expression->visit(*this);
    if (!state_.contains(a->varname))
        add_identifier(a->varname); // Add identifier after checking value_expression to make sure it is not used there
}

void Visitor::visit_do_while(DoWhileLoop* l) {
    l->loop_body->visit(*this);
    l->condition->visit(*this);
}

void Visitor::visit_for_loop(ForLoop* l) {
    l->init_expr->visit(*this);
    l->condition->visit(*this);
    l->loop_body->visit(*this);
    l->incr_expr->visit(*this);
}

void Visitor::visit_if(IfStatement* i) {
    i->condition->visit(*this);
    if (i->has_else())
        scope_union(i->if_com, i->else_com);
}

void Visitor::visit_print(PrintStatement* p) {
    p->to_print->visit(*this);
}

void Visitor::visit_sequence(Sequence* s) {
    s->first->visit(*this);
    s->second->visit(*this);
}

void Visitor::visit_skip(Skip* s) {

}

void Visitor::visit_while(WhileLoop* w) {
    w->condition->visit(*this);
    w->loop_body->visit(*this);
}

void Visitor::visit_a_binary_op(ABinaryOperation* o) {
    o->left_operand->visit(*this);
    o->right_operand->visit(*this);
}

void Visitor::visit_input(InputCommand* i) {

}

void Visitor::visit_num_lit(NumericLiteral* l) {

}

void Visitor::visit_var_ref(VariableRef* v) {
    if (!contains(v->spelling))
            throw InterpreterError(command_, v->source_location, "Variable " + v->spelling + " was used in character " + std::to_string(v->source_location) + " before it was initialized");
}

void Visitor::visit_b_binary_op(BBinaryOperation* o) {
    o->left_operand->visit(*this);
    o->right_operand->visit(*this);
}

void Visitor::visit_bool_lit(BoolLiteral* l) {

}

void Visitor::visit_comp(Comparision* c) {
    c->left_operand->visit(*this);
    c->right_operand->visit(*this);
}

void Visitor::visit_neg(Negation* n) {
    n->expr->visit(*this);
}

void Visitor::clear() {
    identifiers_.resize(1);
    identifiers_.front().clear();
}

void Visitor::add_identifier(const std::string& varname) {
    for (const std::list<std::string>& lst : identifiers_)
        for (const std::string& item : lst)
            if (item == varname)
                return;
        
    identifiers_.front().push_front(varname);
}

bool Visitor::contains(const std::string& varname) const {
    // Search identifiers in current state
    if (state_.contains(varname))
        return true;

     // Search identifiers within the given command
    for (const std::list<std::string>& lst : identifiers_)
        for (const std::string& item : lst)
            if (item == varname)
                return true;

    return false;
}

// Only keep the variables that exist in the scopes from both nodes
void Visitor::scope_union(Statement* first, Statement* second) {
    identifiers_.emplace_front();
    first->visit(*this);
    std::list<std::string> oldScope = std::move(identifiers_.front());
    identifiers_.pop_front();

    identifiers_.emplace_front();
    second->visit(*this);

    auto it = identifiers_.front().begin();
    while (it != identifiers_.front().end()) {
        bool found = false;

        if (state_.contains(*it))
            found = true;
        else {
            for (const std::string& item : oldScope)
                if (item == *it)
                    found = true;
        }

            
        if (!found) {
            auto oldIt = it;
            ++it;
            identifiers_.front().erase(oldIt);
        } else ++it;
    }
}