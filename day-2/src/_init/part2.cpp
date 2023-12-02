/*
--- Day 2: Cube Conundrum Part 2 ---

The Elf says they've stopped producing snow because they aren't getting any water!
He isn't sure why the water stopped; however, he can show you how to get to the water source to check it out for yourself.
It's just up ahead!

As you continue your walk, the Elf poses a second question:
    in each game you played, what is the fewest number of cubes of each color that could have been in the bag to make the game possible?

Again consider the example games from earlier:

Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

    In game 1, the game could have been played with as few as 4 red, 2 green, and 6 blue cubes.
    If any color had even one fewer cube, the game would have been impossible.
    Game 2 could have been played with a minimum of 1 red, 3 green, and 4 blue cubes.
    Game 3 must have been played with at least 20 red, 13 green, and 6 blue cubes.
    Game 4 required at least 14 red, 3 green, and 15 blue cubes.
    Game 5 needed no fewer than 6 red, 3 green, and 2 blue cubes in the bag.

The power of a set of cubes is equal to the numbers of red, green, and blue cubes multiplied together.
The power of the minimum set of cubes in game 1 is 48.
In games 2-5 it was 12, 1560, 630, and 36, respectively.
Adding up these five powers produces the sum 2286.

For each game, find the minimum set of cubes that must have been present.
What is the sum of the power of these sets?
*/

#include "../../include/_init/part1.hpp"
#include "../../include/util/string_util.hpp"

int count_cubes2(std::string game)
{
    if (game.empty())
        return 0;

    std::string game_id = game.substr(0, game.find(": "));
    std::string sets = game.substr(game.find(": ") + 2, game.length() - game.find(": ") - 2);
    std::vector<std::string> sets_vec = split(sets, "; ");

    int red{1}, green{1}, blue{1};
    for (const auto &set : sets_vec)
    {
        std::vector<std::string> set_vec = split(set, ", ");
        for (const auto &cube : set_vec)
        {
            if (cube.find("red") != std::string::npos)
                red = std::max(red, std::stoi(cube.substr(0, cube.find(" "))));
            if (cube.find("green") != std::string::npos)
                green = std::max(green, std::stoi(cube.substr(0, cube.find(" "))));
            if (cube.find("blue") != std::string::npos)
                blue = std::max(blue, std::stoi(cube.substr(0, cube.find(" "))));
        }
    }

    return red * green * blue;
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
        sum += count_cubes2(line);

    return sum;
}
