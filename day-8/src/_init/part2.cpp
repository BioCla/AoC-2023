/*
--- Day 8: Haunted Wasteland Part Two ---

The sandstorm is upon you and you aren't any closer to escaping the wasteland.
You had the camel follow the instructions, but you've barely left your starting position.
It's going to take significantly more steps to escape!

What if the map isn't for people - what if the map is for ghosts? Are ghosts even bound by the laws of spacetime? Only one way to find out.

After examining the maps a bit longer, your attention is drawn to a curious fact:
    the number of nodes with names ending in A is equal to the number ending in Z!
    If you were a ghost, you'd probably just start at every node that ends with A and follow all
    of the paths at the same time until they all simultaneously end up at nodes that end with Z.

For example:

LR

11A = (11B, XXX)
11B = (XXX, 11Z)
11Z = (11B, XXX)
22A = (22B, XXX)
22B = (22C, 22C)
22C = (22Z, 22Z)
22Z = (22B, 22B)
XXX = (XXX, XXX)

Here, there are two starting nodes, 11A and 22A (because they both end with A).
As you follow each left/right instruction, use that instruction to simultaneously navigate away from both nodes you're currently on.
Repeat this process until all of the nodes you're currently on end with Z.
(If only some of the nodes you're on end with Z, they act like any other node and you continue as normal.) In this example, you would proceed as follows:

    Step 0: You are at 11A and 22A.
    Step 1: You choose all of the left paths, leading you to 11B and 22B.
    Step 2: You choose all of the right paths, leading you to 11Z and 22C.
    Step 3: You choose all of the left paths, leading you to 11B and 22Z.
    Step 4: You choose all of the right paths, leading you to 11Z and 22B.
    Step 5: You choose all of the left paths, leading you to 11B and 22C.
    Step 6: You choose all of the right paths, leading you to 11Z and 22Z.

So, in this example, you end up entirely on nodes that end in Z after 6 steps.

Simultaneously start on every node that ends with A.
How many steps does it take before you're only on nodes that end with Z?
*/

#include "../../include/_init/part2.hpp"
#include "../../include/util/string_util.hpp"
#include <numeric>

u_int64_t part2(std::string input_file_path)
{
    std::vector<std::string> document;
    std::fstream document_file(input_file_path, std::ios_base::in);
    while (!document_file.eof())
    {
        std::string line;
        std::getline(document_file, line);
        document.push_back(line);
    }

    std::string directions = document[0];
    document.erase(document.begin());
    std::unordered_map<std::string, std::vector<std::string>> document_map = parse_document(document);

    std::vector<std::string> start_nodes;
    for (const std::pair<const std::string, std::vector<std::string>> &entry : document_map)
        if (entry.first.back() == 'A')
            start_nodes.push_back(entry.first);

    std::vector<u_int> steps_per_node;
    for (std::string &node : start_nodes)
    {
        u_int steps = 0;
        std::string current_node = node;
        for (size_t i = 0; i < directions.size(); i++)
        {
            if (directions[i] == 'L')
                current_node = document_map[current_node][0];
            else if (directions[i] == 'R')
                current_node = document_map[current_node][1];
            steps++;
            if (i == directions.size() - 1)
                i = -1;
            if (current_node.back() == 'Z')
                break;
        }
        steps_per_node.push_back(steps);
    }

    u_int64_t result = steps_per_node[0];
    for (size_t i = 1; i < steps_per_node.size(); i++)
        result = std::lcm(result, steps_per_node[i]);

    return result;
}
