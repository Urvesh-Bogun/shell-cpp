#include "parser.hpp"

#include <string>
#include <string_view>
#include <vector>

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

Command populateCommand(std::vector<std::string> tokens)
{
  Command cmd;
  if (tokens.size() > 0)
  {
    cmd.executable = tokens[0];
  }
  if (tokens.size() > 1)
  {
    for (size_t i = 1; i < tokens.size(); ++i)
    {
      cmd.args.push_back(tokens[i]);
    }
  }
  return cmd;
}
