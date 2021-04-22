#pragma once

#include <exception>
#include <string>

class InterpreterError : public std::exception {
   protected:
    const std::string& command_;
    size_t source_location_;

    std::string exception_str_;

   public:
    InterpreterError(const std::string& command, size_t source_location) : command_(command), source_location_(source_location) {
        std::string markerString(source_location_ + 2, ' ');
        markerString[source_location_] = '^';
        markerString[source_location_ + 1] = '\n';
        exception_str_ = command_ + "\n" + std::move(markerString);
    }
    InterpreterError(const std::string& command, size_t source_location, std::string&& errorMessage) : InterpreterError(command, source_location) {
        exception_str_ += std::move(errorMessage);
    }

    const char* what() const noexcept override {
        return exception_str_.c_str();
    }
};