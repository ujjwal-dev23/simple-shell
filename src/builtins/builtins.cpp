#include <cstdlib>
#include <filesystem>
#include <iostream>
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
    if (builtin_names.count(command_name) > 0) {
        std::cout << command_name << " is a shell builtin\n";
        return;
    }

    const std::string ENV_PATH {std::getenv("PATH")};

    #ifdef _WIN32
        const char os_pathsep {';'};
    #else
        const char os_pathsep {':'};
    #endif

    std::vector<std::string> path_folders {split_string_into_args(ENV_PATH, os_pathsep)};

    for (std::filesystem::path folder : path_folders) {
        std::filesystem::path file_path {folder / command_name};

        using std::filesystem::perms;
        auto file_perms {std::filesystem::status(file_path).permissions()};

        if (std::filesystem::exists(file_path) && (file_perms & perms::owner_exec) == perms::owner_exec) {
            std::cout << command_name << " is " << file_path.string() << '\n';
            return;
        }
    }

    std::cout << command_name << ": not found\n";
}
