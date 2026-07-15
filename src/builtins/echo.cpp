#include <iostream>
#include <string>
#include <vector>

#include "builtins.hpp"

void Builtins::echo(std::vector<std::string>& args) {
    for (int i = 1; i < args.size(); i++) {
        std::cout << args[i] << ' ';
    }

    std::cout << '\n';
}
