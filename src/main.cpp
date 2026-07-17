#include <cstdio>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <sys/types.h>
#include <vector>
#include <spawn.h>
#include <sys/wait.h>

#include "utils/utils.hpp"
#include "builtins/builtins.hpp"

extern char **environ;

void run_external_command(const std::filesystem::path& exec_path, const std::vector<std::string>& args) {
    pid_t child_pid {};

    // create vector of char* for support with posix_spawn()
    std::vector<char *> argv;

    for (const auto& arg : args) {
        // c_str is const char*, const_cast for converting to char*
        argv.push_back(const_cast<char *>(arg.c_str()));
    }
    argv.push_back(nullptr);

    int status {posix_spawn(&child_pid, exec_path.c_str(), nullptr, nullptr, argv.data(), environ)};

    if (status != 0) {
        perror("Error while spawning process: ");
        return;
    }

    if (waitpid(child_pid, &status, 0) == -1) {
        perror("Child process had an error: ");
        return;
    }
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

    std::vector<std::string> args(Utils::split_string_into_args(command, ' '));

    std::optional<std::filesystem::path> exec_path {Utils::get_exec_path(args[0])};

    // Currently case-sensitive
    if (args[0] == "exit") {
        running = false;
    }
    else if (args[0] == "echo") {
        Builtins::echo(args);
    }
    else if (args[0] == "type") {
        Builtins::type(args[1]);
    }
    else if (exec_path) {
        // spawn process
        run_external_command(exec_path.value(), args);
    }
    else {
        std::cout << args[0] << ": command not found\n";
    }
  }

  return 0;
}
