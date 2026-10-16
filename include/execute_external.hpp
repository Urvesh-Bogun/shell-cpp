#ifndef EXECUTE_EXTERNAL_HPP
#define EXECUTE_EXTERNAL_HPP

#include <string>
#include <string_view>
#include <vector>

/*
 * @brief Checks if first arguement is an external executable.
 * @param std::string_view of user's first arguement.
 *
 * Gets a PATH environment variable and builds a std::string to the path of the
 * external executable.
 *
 * Uses X_OK bitwise to check if binary has executable access.
 *
 * @return bool. True if first arguement is an external executable.
 *
 * */
bool isExternal(std::string_view arg1);

/*
 * @brief Converts a std::vector<std::string> to a char * vector to be used in
 * execv().
 * @param std::vector<std::string> refrrence of full tokenised user input.
 *
 * Creates a char * vector from the std::vector<std::string> to be used in
 * execv().
 *
 * @return std::vector<char *> containing the converted string vector.
 * */
std::vector<char *> convertToCharStarVec(std::vector<std::string> &cmd);

/*
 * @brief Performs execution of external executable.
 * @param std::vector<std::string> refrrence of full tokenised user input.
 * @param std::string full path to binary.
 *
 * Forks process:
 * 	Child process executes external executable using execv().
 * 	Parent process waits for child process to finish using waitpid().
 *
 * @return void.
 *
 * */
void executeExternal(std::vector<std::string> &cmd, std::string full_path);

#endif
