#pragma once

#include <string>
#include <string_view>
#include <vector>

/**
 * @breif Splits an std::string into tokens.
 * @param response Full user input.
 *
 * Parses through the string and extracts tokens based on spaces in the input.
 *
 * Final token is added manually (or if no spaces were given).
 *
 * @param response Full user input.
 *
 * @return tokenised Tokenised user input.
 */
std::vector<std::string> tokenise(std::string_view response);

/**
 * @breif Searches the system PATH to resolve an executables full path.
 *
 * Splits PATH environment variable using ":" as a delimiter.
 *
 * Checks if path created is a binary that is an executable using access() and
 * X_OK.
 *
 * @param arg Name of the binary to lookup (e.g. ls, Git, grep).
 *
 * @return Full path to executable if found, empty string ("") if not.
 */
std::string getPathEnv(std::string_view arg);
