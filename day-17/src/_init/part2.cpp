/*
--- Day 17: Clumsy Crucible Part 2 ---

The crucibles of lava simply aren't large enough to provide an adequate supply of lava to the machine parts factory. 
Instead, the Elves are going to upgrade to ultra crucibles.

Ultra crucibles are even more difficult to steer than normal crucibles. Not only do they have trouble going in a 
straight line, but they also have trouble turning!

Once an ultra crucible starts moving in a direction, it needs to move a minimum of four blocks in that direction 
before it can turn (or even before it can stop at the end). However, it will eventually start to get wobbly: 
an ultra crucible can move a maximum of ten consecutive blocks without turning.

In the above example, an ultra crucible could follow this path to minimize heat loss:

2>>>>>>>>1323
32154535v5623
32552456v4254
34465858v5452
45466578v>>>>
143859879845v
445787698776v
363787797965v
465496798688v
456467998645v
122468686556v
254654888773v
432267465553v

In the above example, an ultra crucible would incur the minimum possible heat loss of 94.

Here's another example:

111111111111
999999999991
999999999991
999999999991
999999999991

Sadly, an ultra crucible would need to take an unfortunate path like this one:

1>>>>>>>1111
9999999v9991
9999999v9991
9999999v9991
9999999v>>>>

This route causes the ultra crucible to incur the minimum possible heat loss of 71.

Directing the ultra crucible from the lava pool to the machine parts factory, what is the least heat loss it can incur?
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
        if (!line.empty())
            document.push_back(line);
    }
    document_file.close();

    std::map<std::complex<int>, int> grid;
    for (size_t y = 0; y < document.size(); y++)
        for (size_t x = 0; x < document[y].size(); x++)
            grid[{x, y}] = document[y][x] - '0';

    return minimum_heat_dispersal(4, 10, grid);
}