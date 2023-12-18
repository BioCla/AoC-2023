#include "../../include/util/part1_util.hpp"

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

std::vector<Instruction> parse_instructions1(std::vector<std::string> document)
{
    std::vector<Instruction> instructions;
    for (std::string line : document)
    {
        std::vector<std::string> parts = split(line, " ");
        if (parts.size() != 3)
            continue;
        Instruction instruction;
        if (parts[0] == "U")
            instruction.direction = UP;
        else if (parts[0] == "D")
            instruction.direction = DOWN;
        else if (parts[0] == "L")
            instruction.direction = LEFT;
        else if (parts[0] == "R")
            instruction.direction = RIGHT;
        instruction.distance = std::stoi(parts[1]);
        instruction.color = parts[2].substr(1, parts[2].length() - 1);
        instructions.push_back(instruction);
    }
    return instructions;
}

std::vector<std::vector<char>> create_map(std::vector<Instruction> instructions)
{
    std::complex<int> position(0, 0);
    std::vector<std::vector<char>> map = {{'#'}};
    for (Instruction instruction : instructions)
    {
        switch (instruction.direction)
        {
        case UP:
            for (u_int i = 0; i < instruction.distance; i++)
            {
                if (position.imag() - 1 < 0)
                {
                    std::vector<char> row;
                    for (size_t j = 0; j < map[0].size(); j++)
                        row.push_back('.');
                    map.insert(map.begin(), row);
                    position.imag(0);
                }
                else
                    position.imag(position.imag() - 1);
                map[position.imag()][position.real()] = '#';
            }
            break;
        case DOWN:
            for (u_int i = 0; i < instruction.distance; i++)
            {
                if ((size_t)position.imag() + 1 >= map.size())
                {
                    std::vector<char> row;
                    for (size_t j = 0; j < map[0].size(); j++)
                        row.push_back('.');
                    map.push_back(row);
                }
                position.imag(position.imag() + 1);
                map[position.imag()][position.real()] = '#';
            }
            break;
        case LEFT:
            for (u_int i = 0; i < instruction.distance; i++)
            {
                if (position.real() - 1 < 0)
                {
                    for (size_t j = 0; j < map.size(); j++)
                        map[j].insert(map[j].begin(), '.');
                    position.real(0);
                }
                else
                    position.real(position.real() - 1);
                map[position.imag()][position.real()] = '#';
            }
            break;
        case RIGHT:
            for (u_int i = 0; i < instruction.distance; i++)
            {
                if ((size_t)position.real() + 1 >= map[0].size())
                {
                    for (size_t j = 0; j < map.size(); j++)
                        map[j].push_back('.');
                }
                position.real(position.real() + 1);
                map[position.imag()][position.real()] = '#';
            }
            break;
        default:
            break;
        }
    }
    return map;
}