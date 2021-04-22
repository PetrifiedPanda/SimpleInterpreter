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

    void next_token();
    void accept(Token::Type kind);
    void accept_it();

    Statement* parse_sequence();
    Statement* parse_command();
    Statement* parse_single_or_compound_statement();
    ArithmeticExpression* parse_arithmetic_expression();
    BoolExpression* parse_bool_expression();
   
   private:
    bool next_is_logical_op() const;
};