#include "../../include/util/cards.hpp"

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

std::string *parse_line(std::string line)
{
    std::vector<std::string> _tmp = split(line, ":");
    std::vector<std::string> sets = split(_tmp[1], "|");
    std::string *parsed_line = new std::string[2]{
        sets[0],
        sets[1],
    };

    return parsed_line;
}