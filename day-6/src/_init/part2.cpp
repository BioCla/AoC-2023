/*
--- Day 6: Wait For It Part 2 ---

As the race is about to start, you realize the piece of paper with race times and record distances you got earlier actually just has very bad kerning.
There's really only one race - ignore the spaces between the numbers on each line.

So, the example from before:

Time:      7  15   30
Distance:  9  40  200

...now instead means this:

Time:      71530
Distance:  940200

Now, you have to figure out how many ways there are to win this single race.
In this example, the race lasts for 71530 milliseconds and the record distance you need to beat is 940200 millimeters.
You could hold the button anywhere from 14 to 71516 milliseconds and beat the record, a total of 71503 ways!

How many ways can you beat the record in this one much longer race?
*/

#include "../../include/_init/part2.hpp"
#include "../../include/util/util.hpp"

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

    std::vector<std::string> time_str_split = split(document[0].substr(document[0].find(": ") + 2), " ");
    std::vector<std::string> distance_str_split = split(document[1].substr(document[1].find(": ") + 2), " ");

    std::string time = "";
    std::string distance = "";

    for (std::string time_str : time_str_split)
        if (!time_str.empty())
            time += time_str;

    for (std::string distance_str : distance_str_split)
        if (!distance_str.empty())
            distance += distance_str;

    int64_t time_int = std::stoll(time);
    int64_t distance_int = std::stoll(distance);

    std::cout << std::endl
              << "    Quadratic Solution: " << quadratic_formula(-1, time_int, -distance_int) << std::endl;

    int64_t ways_to_win = 0;

    for (int64_t i = 0; i < time_int; i++)
    {
        int64_t speed = i + 1;
        int64_t time_left = time_int - speed;
        int64_t distance_traveled = speed * time_left;

        if (distance_traveled > distance_int)
            ways_to_win++;
    }

    std::cout << "    Brute Force Solution: ";
    return ways_to_win;
}
