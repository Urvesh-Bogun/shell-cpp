#include <sched.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "execute_externals.hpp"

bool isExternal(std::string_view arg1, Resolver resolved_path)
{
  std::string path = resolved_path(arg1);
  return (!path.empty());
}

std::vector<char *> convertToCharStarVec(const std::vector<std::string> &tokens)
{
  std::vector<char *> argv;

  for (size_t arg{0}; arg < tokens.size(); ++arg)
  {
    argv.push_back(const_cast<char *>(tokens[arg].c_str()));
  }

  argv.push_back(nullptr);

  return argv;
}

void executeExternal(const std::vector<std::string> &tokens,
                     const std::string &full_path)
{
  std::vector<char *> argv = convertToCharStarVec(tokens);

  pid_t pid = fork();

  // Handle failed fork
  if (pid < 0)
  {
    std::cerr << "fork() failed :(" << '\n';
    std::exit(1);
  }

  // Handle child process
  if (pid == 0)
  {
    execv(full_path.c_str(), argv.data());

    // If child process has reached here, we have a problem
    std::cerr << "execv() failed :(" << '\n';
  }
  // Handle parent process
  else
  {
    int status;
    waitpid(pid, &status, 0);
  }
}
