#include "../../include/util/util.hpp"

int energized(std::set<std::pair<std::complex<int>, std::complex<int>>> to_visit, std::map<std::complex<int>, char> grid)
{
    std::set<std::pair<std::complex<int>, std::complex<int>>> visited;
    while (!to_visit.empty())
    {
        auto [pos, dir] = *to_visit.begin();
        to_visit.erase(to_visit.begin());
        while (visited.find({pos, dir}) == visited.end())
        {   
            visited.insert({pos, dir});
            pos += dir;
            if (grid.find(pos) == grid.end())
                break;
            switch (grid[pos])
            {
                case '|': dir = {0, 1}; to_visit.insert({pos, -dir}); break;
                case '-': dir = {-1, 0}; to_visit.insert({pos, -dir}); break;
                case '/': dir = {-dir.imag(), -dir.real()}; break;
                case '\\': dir = {dir.imag(), dir.real()}; break;
                default: break;
            }
        }
    }
    std::set<std::complex<int>> visited_pos;
    for (auto [pos, dir] : visited)
        visited_pos.insert(pos);
    return visited_pos.size() - 1;
}
