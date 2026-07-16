#include <iostream>
#include <string>
#include <vector>

#include "utils/utils.hpp"
#include "builtins/builtins.hpp"

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  bool running {true};

  while (running) {
    std::cout << "$ ";

    std::string command;
    std::getline(std::cin, command);

    std::vector<std::string> args(split_string_into_args(command));

    // Currently case-sensitive
    if (args[0] == "exit") {
        running = false;
    }
    else if (args[0] == "echo") {
        Builtins::echo(args);
    }
    else if (args[0] == "type") {
        int type_code {Builtins::type(args[1])};
        if (type_code == 0) {
            std::cout << args[1] << " is a shell builtin\n";
        }
        else {
            std::cout << args[1] << ": not found\n";
        }
    }
    else {
        std::cout << command << ": command not found\n";
    }
  }
}
