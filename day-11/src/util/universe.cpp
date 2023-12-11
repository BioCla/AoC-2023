#include "../../include/util/universe.hpp"

bool string_contains(std::vector<char> &vector, char character)
{
  for (auto c : vector)
    if (c == character)
      return true;
  return false;
}

void insert_column(std::vector<std::vector<char>> &universe, int column_index, char character)
{
  for (size_t y = 0; y < universe.size(); y++)
    universe[y].insert(universe[y].begin() + column_index, character);
}