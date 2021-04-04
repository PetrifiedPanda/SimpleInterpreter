#pragma once

#include <unordered_map>

class State {
    std::unordered_map<std::string, int> variables_;

   public:
    State();

    void clear();

    void writeVariable(const std::string& varname, int value);

    int readVariable(const std::string& varname) const;

    bool contains(const std::string& varname) const;
};