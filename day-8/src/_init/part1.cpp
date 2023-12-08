/*
--- Day 8: Haunted Wasteland Part 1---

You're still riding a camel across Desert Island when you spot a sandstorm quickly approaching.
When you turn to warn the Elf, she disappears before your eyes! To be fair, she had just finished warning you about ghosts a few minutes ago.

One of the camel's pouches is labeled "maps" - sure enough, it's full of documents (your puzzle input) about how to navigate the desert.
At least, you're pretty sure that's what they are; one of the documents contains a list of left/right instructions,
and the rest of the documents seem to describe some kind of network of labeled nodes.

It seems like you're meant to use the left/right instructions to navigate the network.
Perhaps if you have the camel follow the same instructions, you can escape the haunted wasteland!

After examining the maps for a bit, two nodes stick out: AAA and ZZZ.
You feel like AAA is where you are now, and you have to follow the left/right instructions until you reach ZZZ.

This format defines each node of the network individually.
For example:

RL

AAA = (BBB, CCC)
BBB = (DDD, EEE)
CCC = (ZZZ, GGG)
DDD = (DDD, DDD)
EEE = (EEE, EEE)
GGG = (GGG, GGG)
ZZZ = (ZZZ, ZZZ)

Starting with AAA, you need to look up the next element based on the next left/right instruction in your input.
In this example, start with AAA and go right (R) by choosing the right element of AAA, CCC.
Then, L means to choose the left element of CCC, ZZZ.
By following the left/right instructions, you reach ZZZ in 2 steps.

Of course, you might not find ZZZ right away.
If you run out of left/right instructions, repeat the whole sequence of instructions as necessary: RL really means RLRLRLRLRLRLRLRL...
and so on.
For example, here is a situation that takes 6 steps to reach ZZZ:

LLR

AAA = (BBB, BBB)
BBB = (AAA, ZZZ)
ZZZ = (ZZZ, ZZZ)

Starting at AAA, follow the left/right instructions.
How many steps are required to reach ZZZ?
*/

#include "../../include/_init/part1.hpp"
#include "../../include/util/string_util.hpp"

int part1(std::string input_file_path)
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

    std::string current_node = "AAA";
    u_int steps = 0;
    for (size_t i = 0; i < directions.size(); i++)
    {
        if (directions[i] == 'L')
            current_node = document_map[current_node][0];
        else if (directions[i] == 'R')
            current_node = document_map[current_node][1];
        steps++;
        if (i == directions.size() - 1)
            i = -1;
        if (current_node == "ZZZ")
            break;
    }

    return steps;
}
