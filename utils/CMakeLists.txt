add_library(utils STATIC
    args_parser.h
    input_parser.h

    args_parser.cc
    input_parser.cc)

target_link_libraries(utils PUBLIC Boost::program_options)