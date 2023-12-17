# Advent of Code 2023[^aoc]

Welcome to the repository for solving Advent of Code 2023 challenges! Each day's solution is organized in a separate directory, and this repository uses a Makefile to build the solutions.

## Getting Started

To compile and run a specific day's solution, use the following command:

```bash
make <day>
```

Replace `<day>` with the day number you want to run. For example:

```bash
make 1
```

## Directory Structure

Each day's directory is it's own micro environment, with it's own utilities and source files:

The source code for each day's solution is organized in the format `day-<day>/src/`. The build files are stored, with each build process, in the `build/` directory. Getting replaced any time there's a new build.

## Example Usage

```bash
# Compile and run solution for Day 1
make 1
```

```bash
# Run the program on a specific input file
./main data.txt
```

Feel free to explore and adapt the Makefile and source code as needed for your Advent of Code journey. Happy coding!

[^aoc]:
    [Advent of Code][aoc] – An annual event of Christmas-oriented programming challenges started December 2015.
    Every year since then, beginning on the first day of December, a programming puzzle is published every day for twenty-five days.
    You can solve the puzzle and provide an answer using the language of your choice.

[aoc]: https://adventofcode.com/2023/
[template]: https://github.com/kotlin-hands-on/advent-of-code-kotlin-template/tree/main/.github/template-cleanup