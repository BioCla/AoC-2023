/*
--- Day 3: Gear Ratios Part 2 ---

The engineer finds the missing part and installs it in the engine! 
As the engine springs to life, you jump in the closest gondola, finally ready to ascend to the water source.

You don't seem to be going very fast, though. 
Maybe something is still wrong? Fortunately, the gondola has a phone labeled "help", so you pick it up and the engineer answers.

Before you can explain the situation, she suggests that you look out the window. 
There stands the engineer, holding a phone in one hand and waving with the other. 
You're going so slowly that you haven't even left the station. 
You exit the gondola.

The missing part wasn't the only issue - one of the gears in the engine is wrong. 
A gear is any * symbol that is adjacent to exactly two part numbers. 
Its gear ratio is the result of multiplying those two numbers together.

This time, you need to find the gear ratio of every gear and add them all up so that the engineer can figure out which gear needs to be replaced.

Consider the same engine schematic again:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..

In this schematic, there are two gears. 
The first is in the top left; it has part numbers 467 and 35, so its gear ratio is 16345. 
The second gear is in the lower right; its gear ratio is 451490. 
(The * adjacent to 617 is not a gear because it is only adjacent to one part number.) Adding up all of the gear ratios produces 467835.

What is the sum of all of the gear ratios in your engine schematic?
*/

#include "../../include/util/gears.hpp"

int part2(std::string input_file_path)
{
    std::vector<std::vector<char>> document = get_matrix(input_file_path);
    std::vector<int *> symbol_coordinates = get_symbol_coordinates(document);

    int *numbers = new int[symbol_coordinates.size() * 8];
    int numbers_index = 0;
    int sum = 0;
    for (const auto &coordinate : symbol_coordinates)
    {
        int *nearby_numbers = get_nearby_numbers(document, coordinate);
        int nearby_numbers_count = 0;
        for (int i = 0; i < 8; i++)
        {
            if (nearby_numbers[i] != 0)
            {
                nearby_numbers_count++;
                numbers[numbers_index] = nearby_numbers[i];
                numbers_index++;
            }
        }
        if (nearby_numbers_count == 2)
        {
            sum += numbers[numbers_index - 1] * numbers[numbers_index - 2];
        }
        nearby_numbers = nullptr;
        delete[] nearby_numbers;
    }
    return sum;
}
