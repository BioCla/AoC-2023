/*
--- Day 18: Lavaduct Lagoon Part 1 ---

Thanks to your efforts, the machine parts factory is one of the first factories up and running since the lavafall came back.
However, to catch up with the large backlog of parts requests, the factory will also need a large supply of lava for a while;
the Elves have already started creating a large lagoon nearby for this purpose.

However, they aren't sure the lagoon will be big enough; they've asked you to take a look at the dig plan (your puzzle input).
For example:

R 6 (#70c710)
D 5 (#0dc571)
L 2 (#5713f0)
D 2 (#d2c081)
R 2 (#59c680)
D 2 (#411b91)
L 5 (#8ceee2)
U 2 (#caa173)
L 1 (#1b58a2)
U 2 (#caa171)
R 2 (#7807d2)
U 3 (#a77fa3)
L 2 (#015232)
U 2 (#7a21e3)

The digger starts in a 1 meter cube hole in the ground.
They then dig the specified number of meters up (U), down (D), left (L), or right (R), clearing full 1 meter cubes as they go.
The directions are given as seen from above, so if "up" were north, then "right" would be east, and so on.
Each trench is also listed with the color that the edge of the trench should be painted as an RGB hexadecimal color code.

When viewed from above, the above example dig plan would result in the following loop of trench (#) having been dug out from otherwise ground-level terrain (.):

#######
#.....#
###...#
..#...#
..#...#
###.###
#...#..
##..###
.#....#
.######

At this point, the trench could contain 38 cubic meters of lava.
However, this is just the edge of the lagoon; the next step is to dig out the interior so that it is one meter deep as well:

#######
#######
#######
..#####
..#####
#######
#####..
#######
.######
.######

Now, the lagoon can contain a much more respectable 62 cubic meters of lava.
While the interior is dug out, the edges are also painted according to the color codes in the dig plan.

The Elves are concerned the lagoon won't be large enough; if they follow their dig plan, how many cubic meters of lava could it hold?

*/

#include "../../include/_init/part1.hpp"
#include "../../include/util/part1_util.hpp"

int part1(std::string input_file_path)
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

    std::vector<Instruction> instructions = parse_instructions1(document);
    std::vector<std::vector<char>> map = create_map(instructions);

    std::complex<int> position;
    for (size_t j = 0; j < map[0].size(); j++)
        if (map[0][j] == '#')
        {
            position = std::complex<int>(j + 1, 1);
            break;
        }
    std::vector<std::complex<int>> queue;
    queue.push_back(position);
    while (!queue.empty())
    {
        std::complex<int> current = queue[0];
        queue.erase(queue.begin());
        if (map[current.imag()][current.real()] == '.')
        {
            map[current.imag()][current.real()] = '#';
            if (current.imag() - 1 >= 0)
                queue.push_back(current - std::complex<int>(0, 1));
            if ((size_t)current.imag() + 1 < map.size())
                queue.push_back(current + std::complex<int>(0, 1));
            if (current.real() - 1 >= 0)
                queue.push_back(current - std::complex<int>(1, 0));
            if ((size_t)current.real() + 1 < map[0].size())
                queue.push_back(current + std::complex<int>(1, 0));
        }
    }

    int count = 0;
    for (std::vector<char> row : map)
        for (char c : row)
            if (c == '#')
                count++;

    return count;
}