#include "../../include/util/part2_util.hpp"

enum Direction
{
    RIGHT,
    DOWN,
    LEFT,
    UP
};

std::vector<Instruction> parse_instructions2(std::vector<std::string> document)
{
    std::vector<Instruction> instructions;
    for (std::string line : document)
    {
        std::vector<std::string> parts = split(line, " ");
        if (parts.size() != 3)
            continue;
        parts[2] = parts[2].substr(parts[2].find_first_of("#") + 1, parts[2].length() - 3);
        Instruction instruction;
        instruction.distance = std::stoll(parts[2].substr(0, parts[2].length() - 1), nullptr, 16);
        instruction.direction = parts[2][parts[2].length() - 1] - '0';
        instruction.color = parts[2];
        instructions.push_back(instruction);
    }
    return instructions;
}

// Get the angle coordinates of every moevement
std::vector<std::complex<int64_t>> get_points(std::vector<Instruction> instructions)
{
    std::vector<std::complex<int64_t>> points;
    std::complex<int64_t> position(0, 0);
    points.push_back(position);
    for (Instruction instruction : instructions)
    {
        switch (instruction.direction)
        {
        case RIGHT:
            position.real(position.real() + instruction.distance);
            break;
        case DOWN:
            position.imag(position.imag() + instruction.distance);
            break;
        case LEFT:
            position.real(position.real() - instruction.distance);
            break;
        case UP:
            position.imag(position.imag() - instruction.distance);
            break;
        }
        points.push_back(position);
    }
    return points;
}

u_int64_t shoelace(std::vector<std::complex<int64_t>> points)
{
    u_int64_t area = 0;
    for (size_t i = 0; i < points.size() - 1; i++)
        area += points[i].real() * points[i + 1].imag() - points[i + 1].real() * points[i].imag();
    return (area) / 2;
}