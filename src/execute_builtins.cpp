#include "execute_builtins.hpp"
#include "parser.hpp"

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include <cstdlib>
#include <cstring>
#include <unistd.h>

const std::vector<std::string> builtins = {"exit", "echo", "pwd", "cd", "type"};

const BuiltinHashMap BUILTIN_COMMANDS = {{"echo", builtinEcho},
                                         {"pwd", builtinPwd},
                                         {"cd", builtinCd},
                                         {"type", builtinType}};

bool isBuiltin(std::string_view arg1)
{
  for (size_t i = 0; i < builtins.size(); ++i)
  {
    if (arg1 == builtins[i])
    {
      return true;
    }
  }
  return false;
}

int builtinEcho(const std::vector<std::string> &cmd)
{
  for (size_t i{1}; i < cmd.size(); ++i)
  {
    std::cout << cmd[i] << " ";
  }
  // Add endline
  std::cout << "\n";

  return 0;
}

int builtinPwd(const std::vector<std::string> &cmd)
{
  // Null and 0 as args dynamically allocate memory to the buffer for the file
  // path as needed
  char *cwd = getcwd(NULL, 0);

  std::cout << cwd << '\n';
  free(cwd);

  return 0;
}

int builtinCd(const std::vector<std::string> &cmd)
{
  std::string arg2 = cmd[1];
  const char *path = arg2.c_str();
  chdir(path);

  return 0;
}

int builtinType(const std::vector<std::string> &cmd)
{
  std::string arg2 = cmd[1];

  if (isBuiltin(arg2))
  {
    std::cout << arg2 << " is a shell builtin" << '\n';
  }
  else
  {
    std::string path = getPathEnv(arg2);
    if (!path.empty())
    {
      std::cout << "type is " << path << '\n';
    }
    else
    {
      std::cout << arg2 << ": not found" << '\n';
    }
  }

  return 0;
}

int executeBuiltin(const std::vector<std::string> &cmd)
{
  if (cmd.empty())
  {
    return 0;
  }

  bool b = isBuiltin(cmd[0]);

  if (b)
  {
    auto first = BUILTIN_COMMANDS.find(cmd[0]);
    if (first != BUILTIN_COMMANDS.end())
    {
      return first->second(cmd);
    }
    return 1;
  }
  else
  {
    std::cerr << "Builtin command not found." << '\n';
    return 1;
  }
}
