#include <sstream>
#include <string>

#include "utils.hpp"

std::vector<std::string> split_string_into_args(std::string original_string, char delim) {
    std::stringstream ss(original_string);
    std::string word;
    std::vector<std::string> words;

    while (std::getline(ss, word, delim)) {
        words.push_back(word);
    }

    return words;
}
