#pragma once

#include "../Token.h"

#include "InterpreterError.h"
#include <vector>

class SyntaxError : public InterpreterError {
    std::vector<Token::Type> expected_;
    Token::Type got_;

   public:
    SyntaxError(const std::string& command, size_t sourceLocation, std::initializer_list<Token::Type> expected, Token::Type got);
    SyntaxError(const std::string& command, size_t sourceLocation, Token::Type expected, Token::Type got);
};