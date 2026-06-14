#include "typeCommand.h"
#include "commandMapping.h"
#include <string>
#include <vector>
#include <iostream>

int TypeCommand::execute(const std::vector<std::string>& args) {
  if (args.empty()) return 1;
  std::string commandName {args[0]};

  if (CommandMapping::isBuiltin(commandName)) std::cout << commandName << " is a shell builtin\n";
  else std::cout << commandName << ": not found\n";

  return 0;
}
