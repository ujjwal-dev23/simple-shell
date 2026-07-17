#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "builtins.hpp"
#include "../utils/utils.hpp"

void Builtins::echo(std::vector<std::string>& args) {
    for (int i = 1; i < args.size(); i++) {
        std::cout << args[i] << ' ';
    }

    std::cout << '\n';
}

void Builtins::type(std::string command_name) {
    // Case : builtin
    if (builtin_names.count(command_name) > 0) {
        std::cout << command_name << " is a shell builtin\n";
        return;
    }

    // Case : command in path
    std::optional<std::filesystem::path> exec_path {Utils::get_exec_path(command_name)};
    if (exec_path) {
        std::cout << command_name << " is " << exec_path.value().string() << '\n';
        return;
    }

    // TODO : Add support for custom paths

    // Case : invalid command
    std::cout << command_name << ": not found\n";
}
