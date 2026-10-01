#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <string_view>
#include <vector>

struct Command
{
  std::string executable;
  std::vector<std::string> args;
};

/*
 * @breif Splits an std::string into "tokens".
 *
 * Parses through the string and extracts tokens based on spaces in the input.
 *
 * Final token is added manually (or if no spaces were given).
 *
 * @return std::vector<std::string> of tokenised user inputs.
 *
 * */
std::vector<std::string> tokenise(std::string_view response);

/*
 * @breif Uses "tokens" to populate the Command struct
 *
 * The first element is extracted from the tokens and becomes the executable
 * (e.g. echo).
 *
 * The rest is added to the arugements string vector (e.g. hello world).
 *
 * Will be later improved to work with I/O.
 *
 * @return the Command struct holding the instructions to run.
 * */
Command populateCommand(std::vector<std::string> tokens);

#endif
