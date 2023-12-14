#include "../../include/util/util.hpp"

Grid(char) get_grid(std::vector<std::string> document)
{
    Grid(char) grid;
    for (std::string line : document)
    {
        std::vector<char> row;
        for (char ch : line)
            row.push_back(ch);
        grid.push_back(row);
    }
    return grid;
}

// Rolls the O rocks north until they hit a # rock, another O rock, or the north edge of the grid
Grid(char) roll_north(Grid(char) grid)
{
    bool rolled = false;
    for (size_t i = 0; i < grid.size(); i++)
        for (size_t j = 0; j < grid[i].size(); j++)
            if (grid[i][j] == 'O')
            {
                if (i == 0 || grid[i - 1][j] == '#' || grid[i - 1][j] == 'O')
                    continue;
                grid[i - 1][j] = 'O';
                grid[i][j] = '.';
                rolled = true;
            }
    if (rolled)
        return roll_north(grid);
    return grid;
}

Grid(char) roll_south(Grid(char) grid)
{
    bool rolled = false;
    for (size_t i = 0; i < grid.size(); i++)
        for (size_t j = 0; j < grid[i].size(); j++)
            if (grid[i][j] == 'O')
            {
                if (i == grid.size() - 1 || grid[i + 1][j] == '#' || grid[i + 1][j] == 'O')
                    continue;
                grid[i + 1][j] = 'O';
                grid[i][j] = '.';
                rolled = true;
            }
    if (rolled)
        return roll_south(grid);
    return grid;
}

Grid(char) roll_east(Grid(char) grid)
{
    bool rolled = false;
    for (size_t i = 0; i < grid.size(); i++)
        for (size_t j = 0; j < grid[i].size(); j++)
            if (grid[i][j] == 'O')
            {
                if (j == grid[i].size() - 1 || grid[i][j + 1] == '#' || grid[i][j + 1] == 'O')
                    continue;
                grid[i][j + 1] = 'O';
                grid[i][j] = '.';
                rolled = true;
            }
    if (rolled)
        return roll_east(grid);
    return grid;
}

Grid(char) roll_west(Grid(char) grid)
{
    bool rolled = false;
    for (size_t i = 0; i < grid.size(); i++)
        for (size_t j = 0; j < grid[i].size(); j++)
            if (grid[i][j] == 'O')
            {
                if (j == 0 || grid[i][j - 1] == '#' || grid[i][j - 1] == 'O')
                    continue;
                grid[i][j - 1] = 'O';
                grid[i][j] = '.';
                rolled = true;
            }
    if (rolled)
        return roll_west(grid);
    return grid;
}

Grid(char) spin(Grid(char) grid)
{
    grid = roll_north(grid);
    grid = roll_west(grid);
    grid = roll_south(grid);
    grid = roll_east(grid);
    return grid;
}