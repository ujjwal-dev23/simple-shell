#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  bool running {true};

  while (running) {
    std::cout << "$ ";

    std::string command;
    std::getline(std::cin, command);

    // Currently case-sensitive
    if (command == "exit") {
        running = false;
    }
    else {
        std::cout << command << ": command not found\n";
    }
  }
}
