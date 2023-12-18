#include "../../include/util/util.hpp"

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
