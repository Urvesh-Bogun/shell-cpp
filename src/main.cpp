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
    if (response == "exit")
    {
      loop = false;
    }
    else
    {
      tokenised_response = tokenise(response);
    }
    Command cmd = populateCommand(tokenised_response);
  } while (loop);

  return 0;
}
