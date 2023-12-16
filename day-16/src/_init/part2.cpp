/*
--- Part Two ---

As you try to work out what might be wrong, the reindeer tugs on your shirt and leads you to a nearby control panel. 
There, a collection of buttons lets you align the contraption so that the beam enters from any edge tile and heading away from that edge. 
(You can choose either of two directions for the beam if it starts on a corner; for instance, if the beam starts in the bottom-right corner, 
it can start heading either left or upward.)

So, the beam could start on any tile in the top row (heading downward), any tile in the bottom row (heading upward), 
any tile in the leftmost column (heading right), or any tile in the rightmost column (heading left). To produce lava, 
you need to find the configuration that energizes as many tiles as possible.

In the above example, this can be achieved by starting the beam in the fourth tile from the left in the top row:

.|<2<\....
|v-v\^....
.v.v.|->>>
.v.v.v^.|.
.v.v.v^...
.v.v.v^..\
.v.v/2\\..
<-2-/vv|..
.|<<<2-|.\
.v//.|.v..

Using this configuration, 51 tiles are energized:

.#####....
.#.#.#....
.#.#.#####
.#.#.##...
.#.#.##...
.#.#.##...
.#.#####..
########..
.#######..
.#...#.#..

Find the initial beam configuration that energizes the largest number of tiles; how many tiles are energized in that configuration?
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

    std::map<std::complex<int>, char> grid;
    for (size_t y = 0; y < document.size(); y++)
        for (size_t x = 0; x < document[y].size(); x++)
            grid[{x, y}] = document[y][x];
    
    std::map<std::pair<std::complex<int>, std::complex<int>>, int> starting_positions_and_directions;
    for (size_t x = 0; x < document[0].size(); x++)
    {
        starting_positions_and_directions[{{x, 0}, {0, 1}}] = 0;
        starting_positions_and_directions[{{x, document.size() - 1}, {0, -1}}] = 0;
    }
    for (size_t y = 0; y < document.size(); y++)
    {
        starting_positions_and_directions[{{0, y}, {1, 0}}] = 0;
        starting_positions_and_directions[{{document[0].size() - 1, y}, {-1, 0}}] = 0;
    }

    for (auto [starting_position_and_direction, energized_tiles] : starting_positions_and_directions)
        starting_positions_and_directions[starting_position_and_direction] = energized({starting_position_and_direction}, grid);
    return std::max_element(starting_positions_and_directions.begin(), starting_positions_and_directions.end(), [](auto a, auto b) { return a.second < b.second; })->second + 1;
}