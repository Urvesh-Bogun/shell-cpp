#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include <cstdlib>
#include <cstring>
#include <unistd.h>

const std::vector<std::string> builtins = {"exit", "echo", "pwd", "cd", "type"};

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

void echo(std::vector<std::string> &cmd)
{
  for (size_t i{1}; i < cmd.size(); ++i)
  {
    std::cout << cmd[i] << " ";
  }
  // Add endline
  std::cout << "\n";
}

void pwd()
{
  // Null and 0 as args dynamically allocate memory to the buffer for the file
  // path as needed
  char *cwd = getcwd(NULL, 0);

  std::cout << cwd << '\n';
  free(cwd);
}

void cd(std::string arg2)
{
  const char *path = arg2.c_str();
  chdir(path);
}

void type(std::string_view arg2)
{

  if (isBuiltin(arg2))
  {
    std::cout << arg2 << " is a shell builtin" << '\n';
    return;
  }
  else
  {
    const char *path = getenv("PATH");

    std::string path_string = static_cast<std::string>(path);
    std::string path_so_far;

    for (size_t i{0}; i < path_string.size(); ++i)
    {
      if (path_string[i] == ':')
      {
        std::string full_path =
            path_so_far + "/" + static_cast<std::string>(arg2);

        // Is there a binary we can execute?
        if (access(full_path.c_str(), X_OK) == 0)
        {
          std::cout << "type is " << full_path << '\n';
          return;
        }
        path_so_far.clear();
      }
      else
      {
        path_so_far += path_string[i];
      }
    }
  }
  std::cout << arg2 << ": not found" << '\n';
}

void executeBuiltin(std::vector<std::string> &cmd)
{
  bool b = isBuiltin(cmd[0]);
  if (b)
  {
    std::string builtin = cmd[0];

    if (builtin == "exit")
    {
      exit(EXIT_SUCCESS);
    }
    else if (builtin == "echo")
    {
      echo(cmd);
    }
    else if (builtin == "pwd")
    {
      pwd();
    }
    else if (builtin == "cd")
    {
      cd(cmd[1]);
    }
    else if (builtin == "type")
    {
      type(cmd[1]);
    }
  }
}
