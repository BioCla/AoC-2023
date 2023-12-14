/*
--- Day 14: Parabolic Reflector Dish Part 2 ---

The parabolic reflector dish deforms, but not in a way that focuses the beam. To do that, you'll need to move the rocks to the edges of the platform.
Fortunately, a button on the side of the control panel labeled "spin cycle" attempts to do just that!

Each cycle tilts the platform four times so that the rounded rocks roll north, then west, then south, then east. After each tilt,
the rounded rocks roll as far as they can before the platform tilts in the next direction. After one cycle, the platform will have finished rolling the rounded rocks in those four directions in that order.

Here's what happens in the example above after each of the first few cycles:

After 1 cycle:
.....#....
....#...O#
...OO##...
.OO#......
.....OOO#.
.O#...O#.#
....O#....
......OOOO
#...O###..
#..OO#....

After 2 cycles:
.....#....
....#...O#
.....##...
..O#......
.....OOO#.
.O#...O#.#
....O#...O
.......OOO
#..OO###..
#.OOO#...O

After 3 cycles:
.....#....
....#...O#
.....##...
..O#......
.....OOO#.
.O#...O#.#
....O#...O
.......OOO
#...O###.O
#.OOO#...O

This process should work if you leave it running long enough, but you're still worried about the north support beams.
To make sure they'll survive for a while, you need to calculate the total load on the north support beams after 1000000000 cycles.

In the above example, after 1000000000 cycles, the total load on the north support beams is 64.

Run the spin cycle for 1000000000 cycles. Afterward, what is the total load on the north support beams?
*/

#include "../../include/_init/part2.hpp"
#include "../../include/util/util.hpp"

int score(Grid(char) grid)
{
    int score = 0;
    for (size_t i = 0; i < grid.size(); i++)
        for (size_t j = 0; j < grid[i].size(); j++)
            if (grid[i][j] == 'O')
                score += grid.size() - i;
    return score;
}

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

    Grid(char) rocks_layout = get_grid(document);

    std::unordered_set<Grid(char)> seen;
    for (int i = 0; i < 1000000000; i++)
    {
        rocks_layout = spin(rocks_layout);
        if (seen.find(rocks_layout) != seen.end())
            break;
        seen.insert(rocks_layout);
    }

    std::vector<Grid(char)> repeating_grids;
    for (size_t i = 0; i < seen.size(); i++)
    {
        repeating_grids.push_back(rocks_layout);
        rocks_layout = spin(rocks_layout);
    }

    for (size_t i = 1; i < repeating_grids.size(); i++)
        if (repeating_grids[i] == repeating_grids[0])
            return score(repeating_grids[(1000000000 - seen.size()) % i - 1]);

    return 0;
}