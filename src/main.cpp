#include "execute_builtins.hpp"
#include "parser.hpp"

#include <iostream>
#include <vector>

int main()
{
  bool loop{true};
  do
  {
    std::cout << "[USHELL]$ ";
    std::string response{};
    std::getline(std::cin >> std::ws, response);
    std::vector<std::string> tokenised_response;
    if (!response.empty())
    {
      tokenised_response = tokenise(response);
    }
    const Command cmd = populateCommand(tokenised_response);

    if (isBuiltin(cmd))
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
