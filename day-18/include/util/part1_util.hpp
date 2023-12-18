#ifndef PART_1_UTIL_HPP
#define PART_1_UTIL_HPP

#include "util.hpp"

std::vector<Instruction> parse_instructions1(std::vector<std::string> document);
std::vector<std::vector<char>> create_map(std::vector<Instruction> instructions);

#endif // PART_1_UTIL_HPP