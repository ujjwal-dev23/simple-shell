#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <optional>

namespace Utils {
    std::vector<std::string> split_string_into_args(std::string original_string, char delim);
    std::vector<std::string> get_path_env_folders();
    std::optional<std::filesystem::path> get_exec_path(std::string command_name);
    std::optional<std::filesystem::path> get_exec_path(std::string command_name, std::filesystem::path parent_folder);
}
