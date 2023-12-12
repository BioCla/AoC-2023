#include "../../include/util/arrange.hpp"

std::vector<std::string> split(std::string str, std::string delimiter)
{
  std::vector<std::string> sets;
  size_t pos = 0;
  std::string token;
  while ((pos = str.find(delimiter)) != std::string::npos)
  {
    sets.push_back(str.substr(0, pos));
    str.erase(0, pos + delimiter.length());
  }
  sets.push_back(str);
  return sets;
}

std::tuple<std::string, std::vector<int>> parse_row(std::string row)
{
  std::vector<std::string> info = split(row, " ");
  std::vector<std::string> groups = split(info[1], ",");
  std::vector<int> groups_int;
  for (std::string group : groups)
    groups_int.push_back(std::stoi(group));
  return std::make_tuple(info[0], groups_int);
}

int64_t get_arrangements(std::string row_string, int flag, std::vector<int> groups, std::unordered_map<std::string, u_int64_t> &cache)
{
  std::string groups_string = "";
  for (int group : groups)
    groups_string += std::to_string(group);
  std::string key = row_string + std::to_string(flag == -1 ? 0 : flag) + groups_string + std::to_string(groups.size());
  if (cache.find(key) != cache.end())
    return cache[key];
  if (row_string.size() == 0)
  {
    if ((flag == -1 && groups.size() == 0) || (groups.size() == 1 && flag != -1 && flag == groups[0]))
      return 1;
    return 0;
  }
  int possible_more = 0;
  for (char ch : row_string)
    if (ch == '#' || ch == '?')
      possible_more++;
  if ((flag != -1 && possible_more + flag < std::accumulate(groups.begin(), groups.end(), 0)) || (flag == -1 && possible_more < std::accumulate(groups.begin(), groups.end(), 0)) || (flag != -1 && groups.size() == 0))
    return 0;
  int64_t poss = 0;
  if (row_string[0] == '.' && flag != -1 && flag != groups[0])
    return 0;
  if ((row_string[0] == '.' && flag != -1) || (row_string[0] == '?' && flag != -1 && flag == groups[0]))
    poss += get_arrangements(row_string.substr(1), -1, std::vector<int>(groups.begin() + 1, groups.end()), cache);
  if ((row_string[0] == '#' || row_string[0] == '?') && flag != -1)
    poss += get_arrangements(row_string.substr(1), flag + 1, groups, cache);
  if ((row_string[0] == '?' || row_string[0] == '#') && flag == -1)
    poss += get_arrangements(row_string.substr(1), 1, groups, cache);
  if ((row_string[0] == '?' || row_string[0] == '.') && flag == -1)
    poss += get_arrangements(row_string.substr(1), -1, groups, cache);
  cache[key] = poss;
  return poss;
}
