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

u_int hash(std::string str)
{
    int64_t current_value = 0;
    for (char ch : str)
    {
        u_int ascii_code = ch;
        current_value += ascii_code;
        current_value *= 17;
        current_value %= 256;
    }
    return current_value;
}