#ifndef ARRANGE_HPP
#define ARRANGE_HPP

#include <iostream>
#include <numeric>

std::vector<std::string> split(std::string str, std::string delimiter);
std::tuple<std::string, std::vector<int>> parse_row(std::string row);
int64_t get_arrangements(std::string row_string, int flag, std::vector<int> groups, std::unordered_map<std::string, u_int64_t> &cache);

#endif // ARRANGE_HPP