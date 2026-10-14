#ifndef EXECUTE_BUILTINS_HPP
#define EXECUTE_BUILTINS_HPP

#include <string>
#include <string_view>
#include <vector>

/*
 * @brief Checks if first arguement is a shell builtin.
 * @param std::string_view of user's first arguement.
 *
 * Iterates through predefined array of builtins and checks if the first
 * arguement of user input matches any entries in the array.
 *
 * @return bool. True if first arguement is a shell builtin.
 *
 * */
bool isBuiltin(std::string_view agr1);

/*
 * @brief Prints out user input apart from "echo" command.
 * @param std::vector<std::sting> reference to full user input.
 *
 * Iterates through rest of the string vector and prints each word.
 *
 * @return void.
 *
 * */
void echo(std::vector<std::string> &cmd);

/*
 * @brief Prints current working directoy.
 *
 * Prints char pointer holding the current working directoy using getcwd()
 *
 * cwd() uses NULL and 0 to dynamically allocate memory as we do not know the
 * length of the current directoy.
 *
 * @return void.
 *
 * */
void pwd();

/*
 * @brief Changes user directoy.
 * @param std::string of directoy user wants to change into.
 *
 * Converts std::string to C string (std::string_view not used for safe
 * conversion), which is then passed into the chdir() system call.
 *
 * @return void.
 *
 * */
void cd(std::string arg2);

/*
 * @brief Prints whether a command is a shell builtin or external executable.
 * @param std::string_view of the user's second arguement.
 *
 * First checks if type is a shell builtin using isBuiltin().
 *
 * Then checks if type is an external executable using isExternal().
 *
 * If not, gets the PATH environment variable and builds a std::string to the
 * path of the extenal executable.
 *
 * @return void.
 * */
void type(std::string_view arg2);

/*
 * @brief Performs execution of builtin.
 * @param std::vector<std::string> reference of full tokenised user input.
 *
 * Calls different builtin functions based on user input.
 *
 * @return void.
 *
 * */
void executeBuiltin(std::vector<std::string> &cmd);

#endif
