/*
--- Day 11: Cosmic Expansion Part 2 ---

The galaxies are much older (and thus much farther apart) than the researcher initially estimated.

Now, instead of the expansion you did before, make each empty row or column one million times larger.
That is, each empty row should be replaced with 1000000 empty rows, and each empty column should be replaced with 1000000 empty columns.

(In the example above, if each empty row or column were merely 10 times larger, the sum of the shortest paths between every pair of galaxies would be 1030.
If each empty row or column were merely 100 times larger, the sum of the shortest paths between every pair of galaxies would be 8410.
However, your universe will need to expand far beyond these values.)

Starting with the same initial image, expand the universe according to these new rules, then find the length of the shortest path between every pair of galaxies.
What is the sum of these lengths?
*/

#include "../../include/_init/part2.hpp"
#include "../../include/util/universe.hpp"

int part2(std::string input_file_path)
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

  return 0;
}
