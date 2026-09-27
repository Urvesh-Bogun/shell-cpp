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
