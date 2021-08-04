#include "Error/SyntaxError.h"

SyntaxError::SyntaxError(const std::string& command, size_t source_location, std::initializer_list<Token::Type> expected, Token::Type got) : InterpreterError(command, source_location), expected_(expected), got_(got) {
    exception_str_ += "Syntax Error on character " + std::to_string(source_location_) + "\nExpected token of type ";
    if (expected_.size() == 1)
        exception_str_ += Token::to_string(expected_[0]);
    else {
        int i;
        for (i = 0; i < expected_.size() - 1; ++i) {
            exception_str_ += Token::to_string(expected_[i]) + ", ";
        }

        exception_str_ += "or " + Token::to_string(expected_[i]);
    }

    exception_str_ += ", but got token of type " + Token::to_string(got_);
}

SyntaxError::SyntaxError(const std::string& command, size_t source_location, Token::Type expected, Token::Type got) : SyntaxError(command, source_location, {expected}, got) {}