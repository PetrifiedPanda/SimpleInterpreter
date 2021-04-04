#include "Visitor.h"

#include <stdexcept>

#include "Error/InterpreterError.h"

Visitor::Visitor(const std::string& command, const State& state) : command_(command), identifiers_(), state_(state) {
    identifiers_.emplace_front();
}

void Visitor::visitAssignment(Assignment* a) {
    a->valueExpression->visit(*this);
    if (!state_.contains(a->varname))
        addIdentifier(a->varname); // Add identifier after checking valueExpression to make sure it is not used there
}

void Visitor::visitDoWhile(DoWhileLoop* l) {
    l->loopBody->visit(*this);
    l->condition->visit(*this);
}

void Visitor::visitForLoop(ForLoop* l) {
    l->initExpr->visit(*this);
    l->condition->visit(*this);
    l->loopBody->visit(*this);
    l->incrExpression->visit(*this);
}

void Visitor::visitIf(IfStatement* i) {
    i->condition->visit(*this);
    if (i->hasElse())
        scopeUnion(i->ifCom, i->elseCom);
}

void Visitor::visitPrint(PrintStatement* p) {
    p->toPrint->visit(*this);
}

void Visitor::visitSequence(Sequence* s) {
    s->first->visit(*this);
    s->second->visit(*this);
}

void Visitor::visitSkip(Skip* s) {

}

void Visitor::visitWhile(WhileLoop* w) {
    w->condition->visit(*this);
    w->loopBody->visit(*this);
}

void Visitor::visitABinaryOp(ABinaryOperation* o) {
    o->leftOperand->visit(*this);
    o->rightOperand->visit(*this);
}

void Visitor::visitNumLit(NumericLiteral* l) {

}

void Visitor::visitVarRef(VariableRef* v) {
    if (!contains(v->spelling))
            throw InterpreterError(command_, v->sourceLocation, "Variable " + v->spelling + " was used in character " + std::to_string(v->sourceLocation) + " before it was initialized");
}

void Visitor::visitBBinaryOp(BBinaryOperation* o) {
    o->leftOperand->visit(*this);
    o->rightOperand->visit(*this);
}

void Visitor::visitBoolLit(BoolLiteral* l) {

}

void Visitor::visitComp(Comparision* c) {
    c->leftOperand->visit(*this);
    c->rightOperand->visit(*this);
}

void Visitor::visitNeg(Negation* n) {
    n->expr->visit(*this);
}

void Visitor::clear() {
    identifiers_.resize(1);
    identifiers_.front().clear();
}

void Visitor::addIdentifier(const std::string& varname) {
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
void Visitor::scopeUnion(Command* first, Command* second) {
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