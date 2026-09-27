#include "parser.hpp"

#include <iostream>

int main()
{
  bool loop{true};
  do
  {
    std::cout << "[USHELL]$ ";
    std::string response{};
    std::getline(std::cin >> std::ws, response);
    if (response == "exit")
    {
      loop = false;
    }
    else
    {
      const std::vector<std::string> tokenised_response = tokenise(response);
      for (std::string token : tokenised_response)
        std::cout << token << '\n';
    }
  } while (loop);

  return 0;
}
