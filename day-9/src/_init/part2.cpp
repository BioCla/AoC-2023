/*
--- Day 9: Mirage Maintenance Part 2 ---

Of course, it would be nice to have even more history included in your report.
Surely it's safe to just extrapolate backwards as well, right?

For each history, repeat the process of finding differences until the sequence of differences is entirely zero.
Then, rather than adding a zero to the end and filling in the next values of each previous sequence,
you should instead add a zero to the beginning of your sequence of zeroes, then fill in new first values for each previous sequence.

In particular, here is what the third example history looks like when extrapolating back in time:

5  10  13  16  21  30  45
  5   3   3   5   9  15
   -2   0   2   4   6
      2   2   2   2
        0   0   0

Adding the new values on the left side of each sequence from bottom to top eventually reveals the new left-most history value: 5.

Doing this for the remaining example data above results in previous values of -3 for the first history and 0 for the second history.
Adding all three new values together produces 2.

Analyze your OASIS report again, this time extrapolating the previous value for each history.
What is the sum of these extrapolated values?
*/

#include "../../include/_init/part2.hpp"
#include "../../include/util/string_util.hpp"

int part2(std::string input_file_path)
{
  std::vector<std::vector<int64_t>> values;
  std::fstream document_file(input_file_path, std::ios_base::in);
  while (!document_file.eof())
  {
    std::string line;
    std::getline(document_file, line);
    std::vector<std::string> line_values = split(line, " ");
    std::vector<int64_t> line_values_int;
    for (size_t i = 0; i < line_values.size(); i++)
      if (line_values[i] != "")
        line_values_int.push_back(std::stoll(line_values[i]));
    if (line_values_int.size() > 0)
      values.push_back(line_values_int);
  }

  for (size_t i = 0; i < values.size(); i++)
  {
    std::vector<int64_t> values_reversed;
    for (size_t j = 0; j < values[i].size(); j++)
      values_reversed.push_back(values[i][values[i].size() - j - 1]);
    values[i] = values_reversed;
  }

  std::vector<std::vector<std::vector<int64_t>>> history_of_differences;
  for (size_t i = 0; i < values.size(); i++)
  {
    std::vector<std::vector<int64_t>> history_of_differences_for_value;
    std::vector<int64_t> history_of_differences_for_value_first;
    for (size_t j = 0; j < values[i].size() - 1; j++)
      history_of_differences_for_value_first.push_back(values[i][j + 1] - values[i][j]);
    history_of_differences_for_value.push_back(history_of_differences_for_value_first);
    while (has_non_zero(history_of_differences_for_value[history_of_differences_for_value.size() - 1]))
    {
      std::vector<int64_t> history_of_differences_for_value_next;
      for (size_t j = 0; j < history_of_differences_for_value[history_of_differences_for_value.size() - 1].size() - 1; j++)
        history_of_differences_for_value_next.push_back(history_of_differences_for_value[history_of_differences_for_value.size() - 1][j + 1] - history_of_differences_for_value[history_of_differences_for_value.size() - 1][j]);
      history_of_differences_for_value.push_back(history_of_differences_for_value_next);
    }
    history_of_differences.push_back(history_of_differences_for_value);
  }

  std::vector<int64_t> next_values;
  for (size_t i = 0; i < history_of_differences.size(); i++)
  {
    int64_t next_value = 0;
    for (size_t j = 0; j < history_of_differences[i].size(); j++)
    {
      next_value += history_of_differences[i][j][history_of_differences[i][j].size() - 1];
      history_of_differences[i][j][history_of_differences[i][j].size() - 1] = next_value;
    }
    next_values.push_back(next_value);
  }

  std::vector<int64_t> predictions;
  for (size_t i = 0; i < values.size(); i++)
    predictions.push_back(values[i][values[i].size() - 1] + next_values[i]);

  int64_t sum = 0;
  for (size_t i = 0; i < predictions.size(); i++)
    sum += predictions[i];

  return sum;
}
