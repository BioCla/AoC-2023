#include "../../include/util/maps.hpp"

std::unordered_map<std::string /*directions*/, Position> directions = {
    {"up", {0, -1}},
    {"down", {0, 1}},
    {"left", {-1, 0}},
    {"right", {1, 0}}};

char get_tile(std::vector<std::vector<char>> &map, Position position)
{
  if (position.x < 0 || position.y < 0 || size_t(position.y) >= map.size() || size_t(position.x) >= map[position.y].size())
    return ' ';
  return map[position.y][position.x];
}

bool is_valid_movement(std::vector<std::vector<char>> &map, Position position, std::string direction)
{
  char next_tile = get_tile(map, position + directions[direction]);
  if (next_tile == ' ')
    return false;
  if (direction == "up")
    return next_tile == '|' || next_tile == 'F' || next_tile == '7';
  if (direction == "down")
    return next_tile == '|' || next_tile == 'L' || next_tile == 'J';
  if (direction == "left")
    return next_tile == '-' || next_tile == 'L' || next_tile == 'F';
  if (direction == "right")
    return next_tile == '-' || next_tile == 'J' || next_tile == '7';
  return false;
}

std::vector<Position> get_possible_directions_from_current_position(std::vector<std::vector<char>> &map, Position current_position)
{
  std::vector<Position> possible_directions;
  for (auto direction : directions)
    if (is_valid_movement(map, current_position, direction.first))
      possible_directions.push_back(direction.second);
  return possible_directions;
}