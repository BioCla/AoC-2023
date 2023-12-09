#include "../../include/util/string_util.hpp"

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

bool has_non_zero(std::vector<int64_t> history)
{
  for (size_t i = 0; i < history.size(); i++)
    if (history[i] != 0)
      return true;
  return false;
}
