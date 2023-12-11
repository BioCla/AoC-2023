/*
--- Day 11: Cosmic Expansion Part 1 ---

You continue following signs for "Hot Springs" and eventually come across an observatory.
The Elf within turns out to be a researcher studying cosmic expansion using the giant telescope here.

He doesn't know anything about the missing machine parts; he's only visiting for this research project.
However, he confirms that the hot springs are the next-closest area likely to have people;
he'll even take you straight there once he's done with today's observation analysis.

Maybe you can help him with the analysis to speed things up?

The researcher has collected a bunch of data and compiled the data into a single giant image (your puzzle input).
The image includes empty space (.) and galaxies (#).
For example:

...#......
.......#..
#.........
..........
......#...
.#........
.........#
..........
.......#..
#...#.....

The researcher is trying to figure out the sum of the lengths of the shortest path between every pair of galaxies.
However, there's a catch: the universe expanded in the time it took the light from those galaxies to reach the observatory.

Due to something involving gravitational effects, only some space expands.
In fact, the result is that any rows or columns that contain no galaxies should all actually be twice as big.

In the above example, three columns and two rows contain no galaxies:

   v  v  v
 ...#......
 .......#..
 #.........
>..........<
 ......#...
 .#........
 .........#
>..........<
 .......#..
 #...#.....
   ^  ^  ^

These rows and columns need to be twice as big; the result of cosmic expansion therefore looks like this:

....#........
.........#...
#............
.............
.............
........#....
.#...........
............#
.............
.............
.........#...
#....#.......

Equipped with this expanded universe, the shortest path between every pair of galaxies can be found.
It can help to assign every galaxy a unique number:

....1........
.........2...
3............
.............
.............
........4....
.5...........
............6
.............
.............
.........7...
8....9.......

In these 9 galaxies, there are 36 pairs.
Only count each pair once; order within the pair doesn't matter.
For each pair, find any shortest path between the two galaxies using only steps that move up, down, left, or right exactly one .
or # at a time.
(The shortest path between two galaxies is allowed to pass through another galaxy.)

For example, here is one of the shortest paths between galaxies 5 and 9:

....1........
.........2...
3............
.............
.............
........4....
.5...........
.##.........6
..##.........
...##........
....##...7...
8....9.......

This path has length 9 because it takes a minimum of nine steps to get from galaxy 5 to galaxy 9 (the eight locations marked # plus the step onto galaxy 9 itself).
Here are some other example shortest path lengths:

    Between galaxy 1 and galaxy 7: 15
    Between galaxy 3 and galaxy 6: 17
    Between galaxy 8 and galaxy 9: 5

In this example, after expanding the universe, the sum of the shortest path between all 36 pairs of galaxies is 374.

Expand the universe, then find the length of the shortest path between every pair of galaxies.
What is the sum of these lengths?
*/

#include "../../include/_init/part1.hpp"
#include "../../include/util/universe.hpp"

int part1(std::string input_file_path)
{
  std::vector<std::vector<char>> universe;
  std::fstream document_file(input_file_path, std::ios_base::in);
  while (!document_file.eof())
  {
    std::string line;
    std::getline(document_file, line);
    if (line.size() == 0)
      continue;
    std::vector<char> vector_line(line.begin(), line.end());
    universe.push_back(vector_line);
  }
  document_file.close();

  std::vector<std::vector<char>> expanded_universe;
  for (size_t y = 0; y < universe.size(); y++)
  {
    if (!string_contains(universe[y], '#'))
      expanded_universe.push_back(universe[y]);
    expanded_universe.push_back(universe[y]);
  }

  int expansions = 0;
  for (size_t x = 0; x < universe[0].size(); x++)
  {
    std::vector<char> column;
    for (size_t y = 0; y < universe.size(); y++)
      column.push_back(universe[y][x]);
    if (!string_contains(column, '#'))
    {
      insert_column(expanded_universe, x + expansions, '.');
      expansions++;
    }
  }
  
  std::vector<Position> galaxies;
  for (size_t y = 0; y < expanded_universe.size(); y++)
    for (size_t x = 0; x < expanded_universe[y].size(); x++)
      if (expanded_universe[y][x] == '#')
        galaxies.push_back({int(x), int(y)});

  int total_distance = 0;
  for (size_t i = 0; i < galaxies.size(); i++)
    for (size_t j = i + 1; j < galaxies.size(); j++)
      total_distance += std::abs(galaxies[i].x - galaxies[j].x) + std::abs(galaxies[i].y - galaxies[j].y);
  return total_distance;
}
