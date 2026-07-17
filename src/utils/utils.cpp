#include <filesystem>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "utils.hpp"

std::vector<std::string> Utils::split_string_into_args(std::string original_string, char delim) {
    std::stringstream ss(original_string);
    std::string word;
    std::vector<std::string> words;

    while (std::getline(ss, word, delim)) {
        words.push_back(word);
    }

    return words;
}

// Overload for searching in $PATH
std::optional<std::filesystem::path> Utils::get_exec_path(std::string command_name) {
    const std::string ENV_PATH {std::getenv("PATH")};

    #ifdef _WIN32
        const char os_pathsep {';'};
    #else
        const char os_pathsep {':'};
    #endif

    std::vector<std::string> path_folders {split_string_into_args(ENV_PATH, os_pathsep)};
    for (std::filesystem::path folder : path_folders) {
       std::optional<std::filesystem::path> exec_path {Utils::get_exec_path(command_name, folder)};
        if (exec_path) {
           return exec_path;
       }
    }

    return {};
}

// Overload for searching in a specific path
std::optional<std::filesystem::path> Utils::get_exec_path(std::string command_name, std::filesystem::path parent_folder) {
    std::filesystem::path file_path {parent_folder / command_name};

    using std::filesystem::perms;
    auto file_perms {std::filesystem::status(file_path).permissions()};

    if (std::filesystem::exists(file_path) && (file_perms & perms::owner_exec) == perms::owner_exec) {
        return file_path;
    }

    return {};
}
