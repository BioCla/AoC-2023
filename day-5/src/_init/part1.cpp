/*
--- Day 5: If You Give A Seed A Fertilizer Part 1 ---

You take the boat and find the gardener right where you were told he would be: managing a giant "garden" that looks more to you like a farm.

"A water source? Island Island is the water source!" You point out that Snow Island isn't receiving any water.

"Oh, we had to stop the water because we ran out of sand to filter it with! Can't make snow with dirty water.
Don't worry, I'm sure we'll get more sand soon; we only turned off the water a few days...
weeks...
oh no." His face sinks into a look of horrified realization.

"I've been so busy making sure everyone here has food that I completely forgot to check why we stopped getting more sand!
There's a ferry leaving soon that is headed over in that direction - it's much faster than your boat.
Could you please go check it out?"

You barely have time to agree to this request when he brings up another.
"While you wait for the ferry, maybe you can help us with our food production problem.
The latest Island Island Almanac just arrived and we're having trouble making sense of it."

The almanac (your puzzle input) lists all of the seeds that need to be planted.
It also lists what type of soil to use with each kind of seed, what type of fertilizer to use with each kind of soil,
what type of water to use with each kind of fertilizer, and so on.
Every type of seed, soil, fertilizer and so on is identified with a number,
but numbers are reused by each category - that is, soil 123 and fertilizer 123 aren't necessarily related to each other.

For example:

seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4

The almanac starts by listing which seeds need to be planted: seeds 79, 14, 55, and 13.

The rest of the almanac contains a list of maps which describe how to convert numbers from a source category into numbers in a destination category.
That is, the section that starts with seed-to-soil map: describes how to convert a seed number (the source) to a soil number (the destination).
This lets the gardener and his team know which soil to use with which seeds, which water to use with which fertilizer, and so on.

Rather than list every source number and its corresponding destination number one by one, the maps describe entire ranges of numbers that can be converted.
Each line within a map contains three numbers: the destination range start, the source range start, and the range length.

Consider again the example seed-to-soil map:

50 98 2
52 50 48

The first line has a destination range start of 50, a source range start of 98, and a range length of 2.
This line means that the source range starts at 98 and contains two values: 98 and 99.
The destination range is the same length, but it starts at 50, so its two values are 50 and 51.
With this information, you know that seed number 98 corresponds to soil number 50 and that seed number 99 corresponds to soil number 51.

The second line means that the source range starts at 50 and contains 48 values: 50, 51, ..., 96, 97.
This corresponds to a destination range starting at 52 and also containing 48 values: 52, 53, ..., 98, 99.
So, seed number 53 corresponds to soil number 55.

Any source numbers that aren't mapped correspond to the same destination number.
So, seed number 10 corresponds to soil number 10.

So, the entire list of seed numbers and their corresponding soil numbers looks like this:

seed  soil
0     0
1     1
...   ...
48    48
49    49
50    52
51    53
...   ...
96    98
97    99
98    50
99    51

With this map, you can look up the soil number required for each initial seed number:

    Seed number 79 corresponds to soil number 81.
    Seed number 14 corresponds to soil number 14.
    Seed number 55 corresponds to soil number 57.
    Seed number 13 corresponds to soil number 13.

The gardener and his team want to get started as soon as possible, so they'd like to know the closest location that needs a seed.
Using these maps, find the lowest location number that corresponds to any of the initial seeds.
To do this, you'll need to convert each seed number through other categories until you can find its corresponding location number.
In this example, the corresponding types are:

    Seed 79, soil 81, fertilizer 81, water 81, light 74, temperature 78, humidity 78, location 82.
    Seed 14, soil 14, fertilizer 53, water 49, light 42, temperature 42, humidity 43, location 43.
    Seed 55, soil 57, fertilizer 57, water 53, light 46, temperature 82, humidity 82, location 86.
    Seed 13, soil 13, fertilizer 52, water 41, light 34, temperature 34, humidity 35, location 35.

So, the lowest location number in this example is 35.

What is the lowest location number that corresponds to any of the initial seed numbers?
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
    std::vector<std::string> seeds = split(document[0].substr(document[0].find(": ") + 2, document[0].length() - 1), " ");
    std::vector<int64_t> seeds_int;
    for (size_t i = 0; i < seeds.size(); i++)
        seeds_int.push_back(std::stoll(seeds[i]));

    std::vector<std::vector<int64_t>>
        seed_to_soil_map,
        soil_to_fertilizer_map,
        fertilizer_to_water_map,
        water_to_light_map,
        light_to_temperature_map,
        temperature_to_humidity_map,
        humidity_to_location_map;

    std::string current_map = "";
    for (size_t i = 1; i < document.size(); i++)
    {
        if (document[i].find("map") != std::string::npos)
            current_map = document[i].substr(0, document[i].find(" "));
        else
        {
            std::vector<std::string> map_line = split(document[i], " ");
            if (map_line.size() <= 1 || map_line[0] == "")
                continue;
            if (current_map == "seed-to-soil")
                seed_to_soil_map.push_back({std::stoll(map_line[0]), std::stoll(map_line[1]), std::stoll(map_line[2])});
            else if (current_map == "soil-to-fertilizer")
                soil_to_fertilizer_map.push_back({std::stoll(map_line[0]), std::stoll(map_line[1]), std::stoll(map_line[2])});
            else if (current_map == "fertilizer-to-water")
                fertilizer_to_water_map.push_back({std::stoll(map_line[0]), std::stoll(map_line[1]), std::stoll(map_line[2])});
            else if (current_map == "water-to-light")
                water_to_light_map.push_back({std::stoll(map_line[0]), std::stoll(map_line[1]), std::stoll(map_line[2])});
            else if (current_map == "light-to-temperature")
                light_to_temperature_map.push_back({std::stoll(map_line[0]), std::stoll(map_line[1]), std::stoll(map_line[2])});
            else if (current_map == "temperature-to-humidity")
                temperature_to_humidity_map.push_back({std::stoll(map_line[0]), std::stoll(map_line[1]), std::stoll(map_line[2])});
            else if (current_map == "humidity-to-location")
                humidity_to_location_map.push_back({std::stoll(map_line[0]), std::stoll(map_line[1]), std::stoll(map_line[2])});
        }
    }

    // Find the first line of the seed-to-soil map that contains the seed number (seed_int >= source && seed_int <= source + range)
    // Then, find the corresponding soil number destination (seed - source + destination)
    // Then, find the first line of the soil-to-fertilizer map that contains the soil number (soil_int >= source && soil_int <= source + range)
    // and so on until the location number is found
    std::unordered_map<int64_t, int64_t> seed_to_location_map;
    for (size_t i = 0; i < seeds_int.size(); i++)
    {
        int64_t seed = seeds_int[i];
        int64_t soil = 0;
        int64_t fertilizer = 0;
        int64_t water = 0;
        int64_t light = 0;
        int64_t temperature = 0;
        int64_t humidity = 0;
        int64_t location = 0;
        for (size_t j = 0; j < seed_to_soil_map.size(); j++)
            if (seed >= seed_to_soil_map[j][1] && seed <= seed_to_soil_map[j][1] + seed_to_soil_map[j][2])
            {
                soil = seed - seed_to_soil_map[j][1] + seed_to_soil_map[j][0];
                break;
            }
        for (size_t j = 0; j < soil_to_fertilizer_map.size(); j++)
            if (soil >= soil_to_fertilizer_map[j][1] && soil <= soil_to_fertilizer_map[j][1] + soil_to_fertilizer_map[j][2])
            {
                fertilizer = soil - soil_to_fertilizer_map[j][1] + soil_to_fertilizer_map[j][0];
                break;
            }
        for (size_t j = 0; j < fertilizer_to_water_map.size(); j++)
            if (fertilizer >= fertilizer_to_water_map[j][1] && fertilizer <= fertilizer_to_water_map[j][1] + fertilizer_to_water_map[j][2])
            {
                water = fertilizer - fertilizer_to_water_map[j][1] + fertilizer_to_water_map[j][0];
                break;
            }
        for (size_t j = 0; j < water_to_light_map.size(); j++)
            if (water >= water_to_light_map[j][1] && water <= water_to_light_map[j][1] + water_to_light_map[j][2])
            {
                light = water - water_to_light_map[j][1] + water_to_light_map[j][0];
                break;
            }
        for (size_t j = 0; j < light_to_temperature_map.size(); j++)
            if (light >= light_to_temperature_map[j][1] && light <= light_to_temperature_map[j][2] + light_to_temperature_map[j][1])
            {
                temperature = light - light_to_temperature_map[j][1] + light_to_temperature_map[j][0];
                break;
            }
        for (size_t j = 0; j < temperature_to_humidity_map.size(); j++)
            if (temperature >= temperature_to_humidity_map[j][1] && temperature <= temperature_to_humidity_map[j][2] + temperature_to_humidity_map[j][1])
            {
                humidity = temperature - temperature_to_humidity_map[j][1] + temperature_to_humidity_map[j][0];
                break;
            }
        for (size_t j = 0; j < humidity_to_location_map.size(); j++)
            if (humidity >= humidity_to_location_map[j][1] && humidity <= humidity_to_location_map[j][2] + humidity_to_location_map[j][1])
            {
                location = humidity - humidity_to_location_map[j][1] + humidity_to_location_map[j][0];
                break;
            }
        seed_to_location_map[seed] = location;
    }

    int64_t lowest_location = INT64_MAX;
    for (auto it = seed_to_location_map.begin(); it != seed_to_location_map.end(); it++)
        if (it->second < lowest_location)
            lowest_location = it->second;

    return lowest_location;
}
