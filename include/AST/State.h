#pragma once

#include <string>
#include <unordered_map>

class State {
    std::unordered_map<std::string, int> variables_;

   public:
    State();

    void clear();

    void write_variable(const std::string& varname, int value);

    int read_variable(const std::string& varname) const;

    bool contains(const std::string& varname) const;
};
