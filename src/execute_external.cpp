#include "execute_external.hpp"
#include "parser.hpp"

#include <string>
#include <string_view>

#include <cstddef>
#include <sched.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Sources:
 *
 * execv: https://www.geeksforgeeks.org/c/exec-family-of-functions-in-c/
 *
 * waitpid: https://linux.die.net/man/2/waitpid
 * */

bool isExternal(std::string_view arg1)
{
  std::string path = getPathEnv(arg1);
  if (!path.empty())
  {
    return true;
  }
  else
  {
    return false;
  }
}

void executeExternal(std::vector<std::string> &cmd, std::string full_path)
{
  // Convert std::vector<std::string> &cmd to char * vector
  std::vector<char *> argv;
  for (size_t arg{0}; arg < cmd.size(); ++arg)
  {
    argv.push_back(const_cast<char *>(cmd[arg].c_str()));
  }
  argv.push_back(nullptr);

  pid_t pid = fork();

  // Handle child process
  if (pid == 0)
  {
    execv(full_path.c_str(), argv.data());
  }
  // Handle parent process
  else
  {
    int status;
    waitpid(pid, &status, 0);
  }
}
