#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split_string_into_args(std::string original_string) {
    std::stringstream ss(original_string);
    std::string word;
    std::vector<std::string> words;

    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}

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
        for (int i = 1; i < args.size(); i++) {
            std::cout << args[i] << ' ';
        }

        std::cout << '\n';
    }
    else {
        std::cout << command << ": command not found\n";
    }
  }
}
