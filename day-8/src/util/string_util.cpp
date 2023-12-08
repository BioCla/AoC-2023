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

std::unordered_map<std::string, std::vector<std::string>> parse_document(std::vector<std::string> document)
{
    std::unordered_map<std::string, std::vector<std::string>> document_map;
    for (std::string line : document)
    {
        if (!line.empty())
        {
            std::vector<std::string> split_line = split(line, " = ");
            std::string key = split_line[0];
            std::string value = split_line[1];
            document_map[key] = {
                split(value, ", ")[0].substr(1),
                split(value, ", ")[1].substr(0, split(value, ", ")[1].size() - 1)
            };  
        }
    }
    return document_map;
}