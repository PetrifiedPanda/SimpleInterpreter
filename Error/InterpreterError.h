#pragma once

#include <exception>
#include <string>

class InterpreterError : public std::exception {
   protected:
    const std::string& command_;
    size_t sourceLocation_;

    std::string exceptionStr_;

   public:
    InterpreterError(const std::string& command, size_t sourceLocation) : command_(command), sourceLocation_(sourceLocation) {
        std::string markerString(sourceLocation_ + 2, ' ');
        markerString[sourceLocation_] = '^';
        markerString[sourceLocation_ + 1] = '\n';
        exceptionStr_ = command_ + "\n" + std::move(markerString);
    }
    InterpreterError(const std::string& command, size_t sourceLocation, std::string&& errorMessage) : InterpreterError(command, sourceLocation) {
        exceptionStr_ += std::move(errorMessage);
    }

    const char* what() const noexcept override {
        return exceptionStr_.c_str();
    }
};