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

#ifndef ADVENT_OF_CODE_2021_ARGS_PARSER_H
#define ADVENT_OF_CODE_2021_ARGS_PARSER_H

#include <boost/program_options.hpp>

namespace aoc2022::utils {

enum class SolutionPart { PART_1, PART_2 };

class ArgsParser {
public:
    ArgsParser() noexcept;

    bool parse(int argc, const char* argv[]);

    SolutionPart get_part() const;
    const std::string& get_input_filename() const;

private:
    boost::program_options::options_description descs_;
    boost::program_options::positional_options_description pos_descs_;
    boost::program_options::variables_map vm_;
    bool successful_parsing_;
};

} // namespace aoc2022::utils

#endif // ADVENT_OF_CODE_2021_ARGS_PARSER_H
