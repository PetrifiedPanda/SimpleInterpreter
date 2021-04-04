#include "SyntaxError.h"

SyntaxError::SyntaxError(const std::string& command, size_t sourceLocation, std::initializer_list<Token::Type> expected, Token::Type got) : InterpreterError(command, sourceLocation), expected_(expected), got_(got) {
    exceptionStr_ += "Syntax Error on character " + std::to_string(sourceLocation_) + "\nExpected token of type ";
    if (expected_.size() == 1)
        exceptionStr_ += Token::toString(expected_[0]);
    else {
        int i;
        for (i = 0; i < expected_.size() - 1; ++i) {
            exceptionStr_ += Token::toString(expected_[i]) + ", ";
        }

        exceptionStr_ += "or " + Token::toString(expected_[i]);
    }

    exceptionStr_ += ", but got token of type " + Token::toString(got_);
}

SyntaxError::SyntaxError(const std::string& command, size_t sourceLocation, Token::Type expected, Token::Type got) : SyntaxError(command, sourceLocation, {expected}, got) {}