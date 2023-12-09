#ifndef STRING_UTIL_HPP
#define STRING_UTIL_HPP

#include <iostream>
#include <vector>

std::vector<std::string> split(std::string str, std::string delimiter);
bool has_non_zero(std::vector<int64_t> history);

#endif // STRING_UTIL_HPP