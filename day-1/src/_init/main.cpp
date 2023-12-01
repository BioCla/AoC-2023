#include "../../include/_init/part1.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
        return 1;
    }

    std::string input_file_path = argv[1];

    std::cout << "Part 1: " << part1(input_file_path) << std::endl;
    // std::cout << "Part 2: " << part2(input_file_path) << std::endl;

    return 0;
}