#include "echoCommand.h"
#include <iostream>

int EchoCommand::execute(const std::vector<std::string>& args) {
  for (auto i {0uz}; i < args.size(); ++i) {
    std::cout << args[i];
    if (i + 1 < args.size()) std::cout << ' ';

  }

  std::cout << '\n';

  return 0;
}
