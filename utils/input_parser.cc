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

#include "input_parser.h"

#include <fstream>

namespace aoc2022::utils {

std::list<std::string> parse_file(const std::string& file_name) {
    std::ifstream input(file_name);
    std::list<std::string> lines;
    for (std::string line; std::getline(input, line);) {
        lines.push_back(line);
    }

    return lines;
}

} // namespace aoc2022::utils