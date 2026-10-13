#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <string_view>
#include <vector>

/*
 * @breif Splits an std::string into "tokens".
 * @param std::string_view of full user input.
 *
 * Parses through the string and extracts tokens based on spaces in the input.
 *
 * Final token is added manually (or if no spaces were given).
 *
 * @return std::vector<std::string> of tokenised user inputs.
 *
 * */
std::vector<std::string> tokenise(std::string_view response);

std::string getPathEnv(std::string_view arg2);

#endif
