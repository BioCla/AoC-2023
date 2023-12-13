#include "../../include/util/mirrors.hpp"

std::vector<std::vector<std::string>> subdivide_maps(std::vector<std::string> document)
{
  std::vector<std::vector<std::string>> maps;
  std::vector<std::string> map;
  for (std::string line : document)
  {
    if (line == "-")
    {
      maps.push_back(map);
      map.clear();
      continue;
    }
    map.push_back(line);
  }
  maps.push_back(map);
  return maps;
}

bool is_horizontal_reflection(std::vector<Complex> map, int maxX, int x, bool part2 = false)
{
  bool flag = false;
  for (Complex p : map)
  {
    Complex newP = Complex(x + (x + 1 - p.real()), p.imag());
    if (0 <= newP.real() && newP.real() <= maxX && std::find(map.begin(), map.end(), newP) == map.end())
    {
      if (!part2 || flag)
        return false;
      flag = true;
    }
  }
  return !part2 || flag;
}

bool is_vertical_reflection(std::vector<Complex> map, int maxY, int y, bool part2 = false)
{
  bool flag = false;
  for (Complex p : map)
  {
    Complex newP = Complex(p.real(), y + (y + 1 - p.imag()));
    if (0 <= newP.imag() && newP.imag() <= maxY && std::find(map.begin(), map.end(), newP) == map.end())
    {
      if (!part2 || flag)
        return false;
      flag = true;
    }
  }
  return !part2 || flag;
}

int solve(std::vector<Complex> grid, int maxX, int maxY, bool part2)
{
  for (int x = 0; x < maxX; x++)
    if (is_horizontal_reflection(grid, maxX, x, part2))
      return x + 1;
  for (int y = 0; y < maxY; y++)
    if (is_vertical_reflection(grid, maxY, y, part2))
      return 100 * (y + 1);
  return 0;
}

std::vector<Complex> make_complex(std::vector<std::string> map)
{
  std::vector<Complex> set;
  for (size_t y = 0; y < map.size(); y++)
    for (size_t x = 0; x < map[y].size(); x++)
      if (map[y][x] == '#')
        set.push_back(Complex(x, y));
  return set;
}
