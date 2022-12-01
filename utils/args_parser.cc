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

#include "args_parser.h"

#include <iostream>
#include <stdexcept>

namespace aoc2022::utils {

namespace po = boost::program_options;

ArgsParser::ArgsParser() noexcept : descs_("Options"), successful_parsing_(false) {
    // clang-format off
    descs_.add_options()
        ("help,h", "Help screen")
        ("part", po::value<int>()->default_value(1), "Solution part (1 or 2, default 1)")
        ("fname", po::value<std::string>(), "Input filename");
    // clang-format on

    pos_descs_.add("fname", 1);
}

bool ArgsParser::parse(int argc, const char** argv) {
    po::store(po::command_line_parser(argc, argv).options(descs_).positional(pos_descs_).run(), vm_);

    successful_parsing_ = false;
    if (vm_.contains("help")) {
        std::cout << descs_ << std::endl;
        return successful_parsing_;
    }

    if (!vm_.contains("fname")) {
        std::cout << "Input file name is required" << std::endl;
        return successful_parsing_;
    }

    int part = vm_["part"].as<int>();
    if ((part != 1) && (part != 2)) {
        std::cout << "Invalid solution part" << std::endl;
        return successful_parsing_;
    }

    successful_parsing_ = true;
    return successful_parsing_;
}

SolutionPart ArgsParser::get_part() const {
    if (!successful_parsing_) {
        throw std::runtime_error("Parsing was not successful");
    }

    int part_raw = vm_["part"].as<int>();
    SolutionPart part{SolutionPart::PART_1};

    if (part_raw == 2) {
        part = SolutionPart::PART_2;
    }

    return part;
}
const std::string& ArgsParser::get_input_filename() const {
    if (!successful_parsing_) {
        throw std::runtime_error("Parsing was not successful");
    }

    return vm_["fname"].as<std::string>();
}

} // namespace aoc2022::utils