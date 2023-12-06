/*
--- Day 5: If You Give A Seed A Fertilizer Part 2 ---

Everyone will starve if you only plant such a small number of seeds.
Re-reading the almanac, it looks like the seeds: line actually describes ranges of seed numbers.

The values on the initial seeds: line come in pairs.
Within each pair, the first value is the start of the range and the second value is the length of the range.
So, in the first line of the example above:

seeds: 79 14 55 13

This line describes two ranges of seed numbers to be planted in the garden.
The first range starts with seed number 79 and contains 14 values: 79, 80, ..., 91, 92.
The second range starts with seed number 55 and contains 13 values: 55, 56, ..., 66, 67.

Now, rather than considering four seed numbers, you need to consider a total of 27 seed numbers.

In the above example, the lowest location number can be obtained from seed number 82, which corresponds to soil 84, fertilizer 84, water 84, light 77, temperature 45, humidity 46, and location 46.
So, the lowest location number is 46.

Consider all of the initial seed numbers listed in the ranges on the first line of the almanac.
What is the lowest location number that corresponds to any of the initial seed numbers?
*/

#include "../../include/_init/part2.hpp"
#include "../../include/util/string_util.hpp"

int part2(std::string input_file_path)
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

    int64_t lowest_location = INT64_MAX;

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

    for (size_t i = 0; i < seeds_int.size(); i += 2)
    {
        int64_t seed_range_start = seeds_int[i];
        int64_t seed_range_end = seed_range_start + seeds_int[i + 1];

        for (std::vector<int64_t> seed_to_soil_entry : seed_to_soil_map)
        {
            std::vector<int64_t> seed_to_soil_source = {
                seed_to_soil_entry[1],
                seed_to_soil_entry[1] + seed_to_soil_entry[2]};

            std::vector<int64_t> seed_to_soil_source_overlap = {
                std::max(seed_range_start, seed_to_soil_source[0]),
                std::min(seed_range_end, seed_to_soil_source[1])};

            if (seed_to_soil_source_overlap[0] > seed_to_soil_source_overlap[1])
                continue;

            std::vector<int64_t> destination_mapped_to_overlap = {
                seed_to_soil_source_overlap[0] - seed_to_soil_source[0] + seed_to_soil_entry[0],
                seed_to_soil_source_overlap[1] - seed_to_soil_source[0] + seed_to_soil_entry[0]};

            for (std::vector<int64_t> soil_to_fertilizer_entry : soil_to_fertilizer_map)
            {
                std::vector<int64_t> soil_to_fertilizer_source = {
                    soil_to_fertilizer_entry[1],
                    soil_to_fertilizer_entry[1] + soil_to_fertilizer_entry[2]};

                std::vector<int64_t> soil_to_fertilizer_source_overlap = {
                    std::max(destination_mapped_to_overlap[0], soil_to_fertilizer_source[0]),
                    std::min(destination_mapped_to_overlap[1], soil_to_fertilizer_source[1])};

                if (soil_to_fertilizer_source_overlap[0] > soil_to_fertilizer_source_overlap[1])
                    continue;

                std::vector<int64_t> destination_mapped_to_overlap = {
                    soil_to_fertilizer_source_overlap[0] - soil_to_fertilizer_source[0] + soil_to_fertilizer_entry[0],
                    soil_to_fertilizer_source_overlap[1] - soil_to_fertilizer_source[0] + soil_to_fertilizer_entry[0]};

                for (std::vector<int64_t> fertilizer_to_water_entry : fertilizer_to_water_map)
                {
                    std::vector<int64_t> fertilizer_to_water_source = {
                        fertilizer_to_water_entry[1],
                        fertilizer_to_water_entry[1] + fertilizer_to_water_entry[2]};

                    std::vector<int64_t> fertilizer_to_water_source_overlap = {
                        std::max(destination_mapped_to_overlap[0], fertilizer_to_water_source[0]),
                        std::min(destination_mapped_to_overlap[1], fertilizer_to_water_source[1])};

                    if (fertilizer_to_water_source_overlap[0] > fertilizer_to_water_source_overlap[1])
                        continue;

                    std::vector<int64_t> destination_mapped_to_overlap = {
                        fertilizer_to_water_source_overlap[0] - fertilizer_to_water_source[0] + fertilizer_to_water_entry[0],
                        fertilizer_to_water_source_overlap[1] - fertilizer_to_water_source[0] + fertilizer_to_water_entry[0]};

                    for (std::vector<int64_t> water_to_light_entry : water_to_light_map)
                    {
                        std::vector<int64_t> water_to_light_source = {
                            water_to_light_entry[1],
                            water_to_light_entry[1] + water_to_light_entry[2]};
                        std::vector<int64_t> water_to_light_source_overlap = {
                            std::max(destination_mapped_to_overlap[0], water_to_light_source[0]),
                            std::min(destination_mapped_to_overlap[1], water_to_light_source[1])};

                        if (water_to_light_source_overlap[0] > water_to_light_source_overlap[1])
                            continue;

                        std::vector<int64_t> destination_mapped_to_overlap = {
                            water_to_light_source_overlap[0] - water_to_light_source[0] + water_to_light_entry[0],
                            water_to_light_source_overlap[1] - water_to_light_source[0] + water_to_light_entry[0]};
                        for (std::vector<int64_t> light_to_temperature_entry : light_to_temperature_map)
                        {
                            std::vector<int64_t> light_to_temperature_source = {
                                light_to_temperature_entry[1],
                                light_to_temperature_entry[1] + light_to_temperature_entry[2]};
                            std::vector<int64_t> light_to_temperature_source_overlap = {
                                std::max(destination_mapped_to_overlap[0], light_to_temperature_source[0]),
                                std::min(destination_mapped_to_overlap[1], light_to_temperature_source[1])};

                            if (light_to_temperature_source_overlap[0] > light_to_temperature_source_overlap[1])
                                continue;

                            std::vector<int64_t> destination_mapped_to_overlap = {
                                light_to_temperature_source_overlap[0] - light_to_temperature_source[0] + light_to_temperature_entry[0],
                                light_to_temperature_source_overlap[1] - light_to_temperature_source[0] + light_to_temperature_entry[0]};
                            for (std::vector<int64_t> temperature_to_humidity_entry : temperature_to_humidity_map)
                            {
                                std::vector<int64_t> temperature_to_humidity_source = {
                                    temperature_to_humidity_entry[1],
                                    temperature_to_humidity_entry[1] + temperature_to_humidity_entry[2]};
                                std::vector<int64_t> temperature_to_humidity_source_overlap = {
                                    std::max(destination_mapped_to_overlap[0], temperature_to_humidity_source[0]),
                                    std::min(destination_mapped_to_overlap[1], temperature_to_humidity_source[1])};

                                if (temperature_to_humidity_source_overlap[0] > temperature_to_humidity_source_overlap[1])
                                    continue;

                                std::vector<int64_t> destination_mapped_to_overlap = {
                                    temperature_to_humidity_source_overlap[0] - temperature_to_humidity_source[0] + temperature_to_humidity_entry[0],
                                    temperature_to_humidity_source_overlap[1] - temperature_to_humidity_source[0] + temperature_to_humidity_entry[0]};
                                for (std::vector<int64_t> humidity_to_location_entry : humidity_to_location_map)
                                {
                                    std::vector<int64_t> humidity_to_location_source = {
                                        humidity_to_location_entry[1],
                                        humidity_to_location_entry[1] + humidity_to_location_entry[2]};
                                    std::vector<int64_t> humidity_to_location_source_overlap = {
                                        std::max(destination_mapped_to_overlap[0], humidity_to_location_source[0]),
                                        std::min(destination_mapped_to_overlap[1], humidity_to_location_source[1])};

                                    if (humidity_to_location_source_overlap[0] > humidity_to_location_source_overlap[1])
                                        continue;

                                    std::vector<int64_t> destination_mapped_to_overlap = {
                                        humidity_to_location_source_overlap[0] - humidity_to_location_source[0] + humidity_to_location_entry[0],
                                        humidity_to_location_source_overlap[1] - humidity_to_location_source[0] + humidity_to_location_entry[0]};
                                    if (destination_mapped_to_overlap[0] < lowest_location)
                                        lowest_location = destination_mapped_to_overlap[0];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return lowest_location;
}
