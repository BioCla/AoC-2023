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

int quadratic_formula(int64_t a, int64_t b, int64_t c)
{
    int64_t sqrt_discriminant = sqrt((b * b) - (4 * a * c)) + 1;
    int64_t i = (-b + sqrt_discriminant) / (2 * a);
    int64_t j = (-b - sqrt_discriminant) / (2 * a);
    return j - i;
}