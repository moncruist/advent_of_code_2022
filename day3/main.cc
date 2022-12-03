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
#include "utils/args_parser.h"
#include "utils/input_parser.h"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <array>
#include <span>

using aoc2022::utils::ArgsParser;
using aoc2022::utils::SolutionPart;

namespace {

constexpr std::size_t kItemTypesNum{26*2};

[[nodiscard]] std::int64_t item_index(char item) {
    if ((item >= 'a') && (item <= 'z')) {
        return item - 'a';
    }
    else {
        return item - 'A' + 26;
    }
}

[[nodiscard]] bool is_in_range(char item) {
    return ((item >= 'a') && (item <= 'z')) || ((item >= 'A') && (item <= 'Z'));
}

[[nodiscard]] std::int64_t find_common_item(const std::string& line) {
    std::int64_t result{0};

    assert((line.size() % 2) == 0U);

    std::array<bool, kItemTypesNum> first_rucksack{};
    std::array<bool, kItemTypesNum> second_rucksack{};

    static_assert(first_rucksack.size() == second_rucksack.size());

    for (std::ptrdiff_t i{0}; i < std::ssize(line); i++) {
        assert(is_in_range(line[i]));

        if (i < (std::ssize(line) / 2)) {
            first_rucksack[item_index(line[i])] = true;
        } else {
            second_rucksack[item_index(line[i])] = true;
        }
    }

    for (std::ptrdiff_t i{0}; i < std::ssize(first_rucksack); i++) {
        if (first_rucksack[i] && second_rucksack[i]) {
            result = i + 1;
            break;
        }
    }

    return result;
}

[[nodiscard]] std::int64_t solution_part1(const std::list<std::string>& input) {
    std::int64_t priority_sum{};

    for (const auto& line : input) {
        if (line.empty()) {
            break;
        }

        priority_sum += find_common_item(line);
    }

    return priority_sum;
}

void mark_occurences(const std::string& line, std::span<std::uint8_t> presence, int bit_idx)
{
    for (const auto ch : line) {
        presence[item_index(ch)] |= (1 << bit_idx);
    }
}

[[nodiscard]] std::int64_t find_common_item_span(const std::span<std::uint8_t> presence, int max_bit_idx) {
    std::int64_t result{};
    const int mask = (1 << (max_bit_idx + 1)) - 1;

    for (std::ptrdiff_t i{0}; i < std::ssize(presence); i++) {
        if (presence[i] == mask) {
            result = i + 1;
            break;
        }
    }

    return result;
}

[[nodiscard]] std::int64_t solution_part2(const std::list<std::string>& input) {
    std::int64_t priority_sum{};

    auto it = input.begin();
    std::array<std::uint8_t, kItemTypesNum> item_presence{};
    int bit_idx{0};

    for (std::ptrdiff_t i{0}; i < std::ssize(input); i++, it++) {
        const auto& line = *it;

        if (line.empty()) {
            break;
        }

        mark_occurences(line, std::span{item_presence}, bit_idx);

        if ((i % 3 == 2) || (i == (std::ssize(input) - 1))) {
            priority_sum += find_common_item_span(std::span{item_presence}, bit_idx);
            item_presence.fill(0);
            bit_idx = 0;
        } else {
            bit_idx++;
        }
    }

    return priority_sum;
}

} // namespace

int main(int argc, const char* argv[]) {
    ArgsParser parser;

    if (!parser.parse(argc, argv)) {
        return 1;
    }

    const std::list<std::string> lines{aoc2022::utils::parse_file(parser.get_input_filename())};

    std::cout << "Part 1: " << solution_part1(lines) << std::endl;
    std::cout << "Part 2: " << solution_part2(lines) << std::endl;
    return 0;
}