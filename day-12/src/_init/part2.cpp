/*
--- Day 12: Hot Springs Part 2 ---

As you look out at the field of springs, you feel like there are way more springs than the condition records list.
When you examine the records, you discover that they were actually folded up this whole time!

To unfold the records, on each row, replace the list of spring conditions with five copies of itself (separated by ?)
and replace the list of contiguous groups of damaged springs with five copies of itself (separated by ,).

So, this row:

.# 1

Would become:

.#?.#?.#?.#?.# 1,1,1,1,1

The first line of the above example would become:

???.###????.###????.###????.###????.### 1,1,3,1,1,3,1,1,3,1,1,3,1,1,3

In the above example, after unfolding, the number of possible arrangements for some rows is now much larger:

    ???.### 1,1,3 - 1 arrangement
    .??..??...?##. 1,1,3 - 16384 arrangements
    ?#?#?#?#?#?#?#? 1,3,1,6 - 1 arrangement
    ????.#...#... 4,1,1 - 16 arrangements
    ????.######..#####. 1,6,5 - 2500 arrangements
    ?###???????? 3,2,1 - 506250 arrangements

After unfolding, adding all of the possible arrangement counts together produces 525152.

Unfold your condition records; what is the new sum of possible arrangement counts?
*/

#include "../../include/_init/part2.hpp"
#include "../../include/util/arrange.hpp"


int64_t part2(std::string input_file_path)
{
  std::vector<std::string> document;
  std::fstream document_file(input_file_path, std::ios_base::in);
  while (!document_file.eof())
  {
    std::string line;
    std::getline(document_file, line);
    if (line.size() == 0)
      continue;
    document.push_back(line);
  }
  document_file.close();

  int64_t total = 0;
  std::unordered_map<std::string, u_int64_t> cache;
  for (std::string row : document)
  {
    std::tuple<std::string, std::vector<int>> parsed_row = parse_row(row);
    std::string row_string = std::get<0>(parsed_row);
    std::vector<int> row_groups = std::get<1>(parsed_row);
    std::string unfolded_row_string = "";
    std::vector<int> unfolded_row_groups = {};
    for (int i = 0; i < 5; i++)
    {
      unfolded_row_string += "?";
      unfolded_row_string += row_string;
      for (int group : row_groups)
        unfolded_row_groups.push_back(group);
    }

    total += get_arrangements(unfolded_row_string.substr(1), -1, unfolded_row_groups, cache);
  }
  return total;
}