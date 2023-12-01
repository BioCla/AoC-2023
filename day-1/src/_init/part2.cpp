/*
--- Day 1: Trebuchet?! Part 2---
Your calculation isn't quite right. It looks like some of the digits are actually spelled out with letters: one, two, three, four, five, six, seven, eight, and nine also count as valid "digits".

Equipped with this new information, you now need to find the real first and last digit on each line. For example:

two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen

In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76. Adding these together produces 281.

What is the sum of all of the calibration values?
*/

#include "../../include/_init/part1.hpp"
// digits regex considering possible overlapping matches with lookahead
std::regex re2("(?=(one|two|three|four|five|six|seven|eight|nine|\\d)).");
// Map of digit strings to their integer values
std::unordered_map<std::string, int> map = {
    {"1", 1},
    {"2", 2},
    {"3", 3},
    {"4", 4},
    {"5", 5},
    {"6", 6},
    {"7", 7},
    {"8", 8},
    {"9", 9},
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
};

// Function to calculate calibration value for a single line
int calibrate2(const std::string &line)
{
    std::smatch match;
    std::string _tmp = line;
    std::vector<int> digits;

    while (std::regex_search(_tmp, match, re2))
    {
        digits.push_back(map[match.str(1)]);
        _tmp = match.suffix().str();
    }

    if (digits.size() > 0)
        return 10 * digits[0] + digits[digits.size() - 1];
    else
        return 0;
}

int part2(std::string input_file_path)
{
    std::vector<std::string> document;
    std::fstream document_file(input_file_path, std::ios_base::in);
    while (!document_file.eof())
    {
        std::string line;
        std::getline(document_file, line);
        document.push_back(line);
    }

    int sum = 0;
    for (const auto &line : document)
        sum += calibrate2(line);

    return sum;
}
