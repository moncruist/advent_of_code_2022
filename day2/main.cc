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

using aoc2022::utils::ArgsParser;
using aoc2022::utils::SolutionPart;

namespace {

enum class Choice { ROCK = 0, PAPER, SCISSOR };

static constexpr std::int64_t kLoseScore{0};
static constexpr std::int64_t kDrawScore{3};
static constexpr std::int64_t kWinScore{6};

[[nodiscard]] std::int64_t get_choice_score(Choice choice) noexcept {
    static constexpr std::size_t kChoiceNum{static_cast<std::size_t>(Choice::SCISSOR) + 1U};
    static constexpr std::array<std::int32_t, kChoiceNum> kMapping{{1, 2, 3}};
    return kMapping[static_cast<std::size_t>(choice)];
}

[[nodiscard]] std::int64_t get_score(Choice player1, Choice player2) noexcept {

    if (player1 == player2) {
        return kDrawScore;
    }

    switch (player1) {
        case Choice::ROCK:
            return (player2 == Choice::PAPER) ? kWinScore : kLoseScore;

        case Choice::PAPER:
            return (player2 == Choice::SCISSOR) ? kWinScore : kLoseScore;

        case Choice::SCISSOR:
            return (player2 == Choice::ROCK) ? kWinScore : kLoseScore;

        default:
            assert(false);
            return kLoseScore;
    }
}

[[nodiscard]] Choice player1_choice(char coded) noexcept {
    switch (coded) {
        case 'A':
            return Choice::ROCK;

        case 'B':
            return Choice::PAPER;

        case 'C':
            return Choice::SCISSOR;

        default:
            assert(false);
            return Choice::ROCK;
    }
}

[[nodiscard]] Choice player2_choice(char coded) noexcept {
    switch (coded) {
        case 'X':
            return Choice::ROCK;

        case 'Y':
            return Choice::PAPER;

        case 'Z':
            return Choice::SCISSOR;

        default:
            assert(false);
            return Choice::ROCK;
    }
}

[[nodiscard]] std::int64_t solution_part1(const std::list<std::string>& input) noexcept {
    std::int64_t total_score{};

    for (const auto& line : input) {
        if (line.empty()) {
            break;
        }

        const Choice player1{player1_choice(line.at(0))};
        const Choice player2{player2_choice(line.at(2))};

        total_score += get_choice_score(player2) + get_score(player1, player2);
    }

    return total_score;
}

enum class Outcome {
    LOSE,
    DRAW,
    WIN
};

[[nodiscard]] Outcome desired_outcome(char coded) noexcept {
    switch (coded) {
        case 'X':
            return Outcome::LOSE;

        case 'Y':
            return Outcome::DRAW;

        case 'Z':
            return Outcome::WIN;

        default:
            assert(false);
            return Outcome::LOSE;
    }
}

[[nodiscard]] std::int64_t outcome_score(Outcome outcome) noexcept {
    static constexpr std::size_t kOutcomeNum{static_cast<std::size_t>(Outcome::WIN) + 1U};
    static constexpr std::array<std::int64_t, kOutcomeNum> kMapping{{kLoseScore, kDrawScore, kWinScore}};

    return kMapping[static_cast<std::size_t>(outcome)];
}

[[nodiscard]] Choice player2_choice_for_outcome(Choice player1, Outcome desired_outcome) noexcept {
    if (desired_outcome == Outcome::DRAW) {
        return player1;
    }

    switch (player1) {
        case Choice::ROCK:
            return (desired_outcome == Outcome::WIN) ? Choice::PAPER : Choice::SCISSOR;

        case Choice::PAPER:
            return (desired_outcome == Outcome::WIN) ? Choice::SCISSOR : Choice::ROCK;

        case Choice::SCISSOR:
            return (desired_outcome == Outcome::WIN) ? Choice::ROCK : Choice::PAPER;

        default:
            assert(false);
            return player1;
    }
}

[[nodiscard]] std::int64_t solution_part2(const std::list<std::string>& input) noexcept {
    std::int64_t total_score{};

    for (const auto& line : input) {
        if (line.empty()) {
            break;
        }

        const Choice player1{player1_choice(line.at(0))};
        const Outcome outcome{desired_outcome(line.at(2))};

        const Choice player2{player2_choice_for_outcome(player1, outcome)};

        total_score += get_choice_score(player2) + outcome_score(outcome);
    }

    return total_score;
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