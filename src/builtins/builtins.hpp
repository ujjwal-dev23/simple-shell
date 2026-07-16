#pragma once

#include <string>
#include <unordered_set>
#include <vector>

namespace Builtins {
    const std::unordered_set<std::string> builtin_names {"echo", "type", "exit"};
    void echo(std::vector<std::string>& args);
    void type(std::string command_arg);
}
