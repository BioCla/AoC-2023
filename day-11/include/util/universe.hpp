#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <iostream>

struct Position
{
  int x;
  int y;
};

bool string_contains(std::vector<char> &vector, char character);
void insert_column(std::vector<std::vector<char>> &universe, int column_index, char character);

#endif // UNIVERSE_HPP