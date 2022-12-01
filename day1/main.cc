// advent_of_code_2022
// Copyright (C) 2022 Konstantin Zhukov
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "solution.h"

#include <iostream>

#include "utils/args_parser.h"
#include "utils/input_parser.h"

using aoc2022::utils::ArgsParser;
using aoc2022::utils::SolutionPart;

int main(int argc, const char* argv[]) {
    ArgsParser parser;

    if (!parser.parse(argc, argv)) {
        return 1;
    }

    const std::list<std::string> lines{aoc2022::utils::parse_file(parser.get_input_filename())};

    std::cout << "Part 1: " << aoc2022::day1::solution_part1(lines) << std::endl;
    std::cout << "Part 2: " << aoc2022::day1::solution_part2(lines) << std::endl;
}