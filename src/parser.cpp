#include "parser.hpp"

#include <string>
#include <string_view>
#include <vector>

#include <unistd.h>

std::vector<std::string> tokenise(std::string_view response)
{
  std::vector<std::string> tokenised{};
  std::string token{};

  for (size_t i{0}; i < response.size(); ++i)
  {
    if (response[i] != ' ')
    {
      token += response[i];
    }
    else
    {
      tokenised.push_back(token);
      token = "";
    }
  }

  // Pushes back last token or if only one token was given (no space)
  if (!token.empty())
  {
    tokenised.push_back(token);
  }
  return tokenised;
}

std::string getPathEnv(std::string_view arg)
{
  const char *path = getenv("PATH");

  std::string path_string = static_cast<std::string>(path);
  std::string path_so_far;

  for (size_t i{0}; i < path_string.size(); ++i)
  {
    if (path_string[i] == ':')
    {
      std::string full_path = path_so_far + "/" + static_cast<std::string>(arg);

      // Is there a binary we can execute?
      if (access(full_path.c_str(), X_OK) == 0)
      {
        return full_path;
      }
      path_so_far.clear();
    }
    else
    {
      path_so_far += path_string[i];
    }
  }
  return "";
}
