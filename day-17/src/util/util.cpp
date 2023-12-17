#include "../../include/util/util.hpp"

int minimum_heat_dispersal(int min_steps, int max_steps, std::map<std::complex<int>, int> grid, int steps)
{
    std::set<std::tuple<int, int, std::complex<int>, std::complex<int>>> todo = {{0, 0, 0, 1}, {0, 0, 0, 1_i}};
    std::set<std::tuple<std::complex<int>, std::complex<int>>> seen;

    while (!todo.empty())
    {
        auto [val, _, pos, dir] = *todo.begin();
        todo.erase(todo.begin());

        if (pos == grid.rbegin()->first) return val;
        if (seen.find({pos, dir}) != seen.end()) continue;
        seen.insert({pos, dir});

        for (auto movement : {1_i / dir, -1_i / dir})
            for (int i = min_steps; i <= max_steps; i++)
                if (grid.find(pos + movement * i) != grid.end())
                {
                    int value = 0;
                    for (int j = 1; j <= i; j++)
                        value += grid[pos + movement * j];
                    todo.insert({val + value, ++steps, pos + movement * i, movement});
                }
    }
    return -1;
}