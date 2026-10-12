#include "execute_builtins.hpp"
#include "parser.hpp"

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <vector>

int main()
{
  // Start at home directory if set in env
  const char *home_dir = getenv("HOME");
  if (home_dir != nullptr)
  {
    chdir(home_dir);
  }

  bool loop{true};
  do
  {
    std::cout << "[USHELL]$ ";
    std::string response{};
    std::getline(std::cin >> std::ws, response);
    std::vector<std::string> cmd;
    if (!response.empty())
    {
      cmd = tokenise(response);
    }

    if (isBuiltin(cmd[0]))
    {
      executeBuiltin(cmd);
    }
    else
    {
      std::cout << "Command unkown" << '\n';
    }
  } while (loop);

  return 0;
}
