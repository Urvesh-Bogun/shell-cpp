#pragma once

#include "parser.hpp"

#include <string>
#include <string_view>
#include <vector>

// Alias for function pointer
using Resolver = std::string (*)(std::string_view);

/**
 * @brief Checks if first arguement is an external executable.
 *
 * Gets a PATH environment variable and builds a std::string to the path of the
 * external executable.
 *
 * Uses X_OK bitwise to check if binary has executable access.
 *
 * @param arg1 Read-only string of user's first argument.
 * @param resolved_path Function pointer to resolve external executable paths
 * (defaults to getPathEnv, otherwise mock path function for unit testing).
 *
 * @return True if first arguement is an external executable.
 */
bool isExternal(std::string_view arg1, Resolver resolved_path = getPathEnv);

/**
 * @brief Converts a std::vector<std::string> to a char * vector to be used in
 * execv().
 *
 * Creates a char * vector from the std::vector<std::string> to be used in
 * execv().
 *
 * @param cmd Reference of full tokenised user input.
 *
 * @return argv The converted string vector.
 */
std::vector<char *> convertToCharStarVec(std::vector<std::string> &cmd);

/**
 * @brief Performs execution of external executable.
 *
 * Forks process:
 * 	Child process executes external executable using execv().
 * 	Parent process waits for child process to finish using waitpid().
 *
 * @param cmd Reference of full tokenised user input.
 * @param full_path Full path to binary.
 *
 * @return void.
 */
void executeExternal(std::vector<std::string> &cmd, std::string full_path);
