#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <unordered_set>

#define Grid(type) std::vector<std::vector<type>>

Grid(char) get_grid(std::vector<std::string> document);
Grid(char) roll_north(Grid(char) grid);
Grid(char) roll_south(Grid(char) grid);
Grid(char) roll_east(Grid(char) grid);
Grid(char) roll_west(Grid(char) grid);
Grid(char) spin(Grid(char) grid);

namespace std {
    template<>
    struct hash<Grid(char)> {
        size_t operator()(const Grid(char) &grid) const {
            size_t hash = 0;
            for (size_t i = 0; i < grid.size(); i++)
                for (size_t j = 0; j < grid[i].size(); j++)
                    hash ^= grid[i][j] + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            return hash;
        }
    };
}

#endif // UTIL_HPP