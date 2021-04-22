#include "State.h"

State::State() : variables_() {}

void State::clear() {
    variables_.clear();
}

void State::write_variable(const std::string& varname, int value) {
    if (variables_.count(varname) != 0)
        variables_[varname] = value;
    else
        variables_.insert(std::make_pair(varname, value));
}

int State::read_variable(const std::string& varname) const {
    return variables_.at(varname);
}

bool State::contains(const std::string& varname) const {
    return variables_.count(varname) != 0;
}