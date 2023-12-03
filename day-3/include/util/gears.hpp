#ifndef GEARS_HPP
#define GEARS_HPP

#include <iostream>
#include <fstream>

std::vector<std::vector<char>> get_matrix(std::string input_file_path);
std::vector<int *> get_symbol_coordinates(std::vector<std::vector<char>> matrix);
int *get_nearby_numbers(std::vector<std::vector<char>> matrix, int *coordinate);

#endif // GEARS_HPP