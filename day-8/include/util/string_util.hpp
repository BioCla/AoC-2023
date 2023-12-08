#ifndef STRING_UTIL_HPP
#define STRING_UTIL_HPP

#include <iostream>
#include <vector>

std::vector<std::string> split(std::string str, std::string delimiter);
std::unordered_map<std::string, std::vector<std::string>> parse_document(std::vector<std::string> document);

#endif // STRING_UTIL_HPP