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

// 0 - Builtin, 1 - Executable, -1 - Invalid
int Builtins::type(std::string command_arg) {
   if (builtin_names.count(command_arg) > 0) {
       return 0;
   }
   else {
       return -1;
   }
}
