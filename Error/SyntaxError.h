#pragma once

#include "../Token.h"

#include "InterpreterError.h"
#include <vector>

class SyntaxError : public InterpreterError {
    std::vector<Token::Type> expected_;
    Token::Type got_;

   public:
    SyntaxError(const std::string& command, size_t source_location, std::initializer_list<Token::Type> expected, Token::Type got);
    SyntaxError(const std::string& command, size_t source_location, Token::Type expected, Token::Type got);
};