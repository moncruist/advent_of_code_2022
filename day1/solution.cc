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

#include <numeric>
#include <set>

namespace aoc2022::day1 {

std::int64_t solution_part1(const std::list<std::string>& input) {
    std::int64_t max_calories{0}, current_elf_callories{0};

    for (const auto& line : input) {
        if (line.empty()) {
            max_calories = std::max(max_calories, current_elf_callories);
            current_elf_callories = 0;
            continue;
        }

        const std::int64_t callories = std::stoll(line);
        current_elf_callories += callories;
    }

    return max_calories;
}

std::int64_t solution_part2(const std::list<std::string>& input) {
    std::multiset<std::int64_t> max_calories;
    std::int64_t current_elf_callories{0};

    for (const auto& line : input) {
        if (line.empty()) {
            max_calories.insert(current_elf_callories);
            while (max_calories.size() > 3U) {
                max_calories.erase(max_calories.begin());
            }
            current_elf_callories = 0;
            continue;
        }

        const std::int64_t callories = std::stoll(line);
        current_elf_callories += callories;
    }

    return std::accumulate(max_calories.begin(), max_calories.end(), 0);
}

} // namespace aoc2022::day1