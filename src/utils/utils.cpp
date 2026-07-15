#include <sstream>

#include "utils.hpp"

std::vector<std::string> split_string_into_args(std::string original_string) {
    std::stringstream ss(original_string);
    std::string word;
    std::vector<std::string> words;

    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}
