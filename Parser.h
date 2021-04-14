#pragma once

#include <list>

#include "Token.h"
#include "AST/AST.h"

class Parser {
    const std::string& command_;
    std::list<Token> tokens_;
    Token currentToken_;

   public:
    Parser();
    Parser(const std::string& command, std::list<Token>&& tokens);

    void nextToken();
    void accept(Token::Type kind);
    void acceptIt();

    Statement* parseSequence();
    Statement* parseCommand();
    Statement* parseSingleOrCompoundStatement();
    ArithmeticExpression* parseArithmeticExpression();
    BoolExpression* parseBoolExpression();

    bool nextIsLogicalOp() const;
};