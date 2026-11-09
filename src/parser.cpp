#include <unistd.h>

#include <string>
#include <string_view>
#include <vector>

#include "parser.hpp"

bool isOperator(std::string_view s)
{
  return (s == ">" || s == ">>" || s == "<" || s == "|" || s == "&");
}

std::vector<std::string> tokenise(std::string_view response)
{
  std::vector<std::string> tokenised{};
  std::string token{};

  bool double_quote = false;
  bool single_quote = false;
  size_t i{0};

  while (i < response.size())
  {
    char c = response[i];

    // Double quote (not single)
    if (c == '"' && !single_quote)
    {
      double_quote = !double_quote;
      ++i;
      continue;
    }

    // Single quote (not quote)
    if (c == '\'' && !double_quote)
    {
      single_quote = !single_quote;
      ++i;
      continue;
    }

    // Space (not quote)
    if (c == ' ' && !double_quote && !single_quote)
    {
      if (!token.empty())
      {
        tokenised.push_back(token);
        token.clear();
      }
      ++i;
      continue;
    }

    // Operators (not in double quote)
    else if ((c == '>' || c == '<' || c == '|' || c == '&') && !double_quote &&
             !single_quote)
    {
      if (!token.empty())
      {
        tokenised.push_back(token);
        token.clear();
      }

      // Check next value if it is another '>'
      if (c == '>' && i + 1 < response.size() && response[i + 1] == '>')
      {
        tokenised.push_back(">>");
        i += 2;
      }
      else
      {
        tokenised.push_back(std::string(1, c));
        ++i;
      }
      continue;
    }

    // Normal characters
    token.push_back(c);
    ++i;
  }

  // Push back whats left
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
