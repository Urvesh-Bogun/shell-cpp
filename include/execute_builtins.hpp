#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

// Alias for builtin function handler (usually takes in tokens)
using Handler = int (*)(const std::vector<std::string> &);

// Alias for HashMap to store command names and corresponding handler
using BuiltinHashMap = std::unordered_map<std::string, Handler>;

extern const BuiltinHashMap BUILTIN_COMMANDS;

/**
 * @brief Checks if first arguement is a shell builtin.
 *
 * Iterates through predefined array of builtins and checks if the first
 * arguement of user input matches any entries in the array.
 *
 * @param arg1 User's first argument.
 *
 * @return True if first arguement is a shell builtin.
 */
bool isBuiltin(std::string_view arg1);

/**
 * @brief Prints out user input apart from "echo" command.
 *
 * Iterates through rest of the string vector and prints each word.
 *
 * @param cmd Reference to full user input.
 *
 * @return int.
 */
int builtinEcho(const std::vector<std::string> &cmd);

/**
 * @brief Prints current working directory.
 *
 * Prints char pointer holding the current working directoy using getcwd()
 *
 * cwd() uses NULL and 0 to dynamically allocate memory as we do not know the
 * length of the current directory.
 *
 * @return int.
 */
int builtinPwd(const std::vector<std::string> &cmd);

/**
 * @brief Changes user directoy.
 *
 * Converts std::string to C string (std::string_view not used for safe
 * conversion), which is then passed into the chdir() system call.
 *
 * @param arg2 Directoy user wants to change into.
 *
 * @return int.
 */
int builtinCd(const std::vector<std::string> &cmd);

/**
 * @brief Prints whether a command is a shell builtin or external executable.
 *
 * First checks if type is a shell builtin using isBuiltin().
 *
 * Then checks if type is an external executable using isExternal().
 *
 * If not, gets the PATH environment variable and builds a std::string to the
 * path of the extenal executable.
 *
 * @param arg2 The user's second argument.
 *
 * @return int.
 */
int builtinType(const std::vector<std::string> &cmd);

/**
 * @brief Performs execution of builtin.
 *
 * Calls different builtin functions based on user input.
 *
 * @param cmd Reference of full tokenised user input.
 *
 * @return int.
 */
int executeBuiltin(const std::vector<std::string> &cmd);
