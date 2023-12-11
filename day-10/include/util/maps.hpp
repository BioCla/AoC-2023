#ifndef MAPS_HPP
#define MAPS_HPP

#include <iostream>

struct Position
{
  int x; // Left to right
  int y; // Top to bottom

  Position operator+(const Position &other)
  {
    return {x + other.x, y + other.y};
  }
  Position operator-(const Position &other)
  {
    return {x - other.x, y - other.y};
  }
  bool operator==(const Position &other)
  {
    return x == other.x && y == other.y;
  }
  bool operator!=(const Position &other)
  {
    return x != other.x || y != other.y;
  }
  friend std::ostream &operator<<(std::ostream &os, const Position &position)
  {
    os << "(" << position.x << ", " << position.y << ")";
    return os;
  }
};

char get_tile(std::vector<std::vector<char>> &map, Position position);
bool is_valid_movement(std::vector<std::vector<char>> &map, Position position, std::string direction);
std::vector<Position> get_possible_directions_from_current_position(std::vector<std::vector<char>> &map, Position current_position);

template <typename T>
bool contains(std::vector<T> vector, T element)
{
  for (auto vector_element : vector)
    if (vector_element == element)
      return true;
  return false;
}

#endif // MAPS_HPP