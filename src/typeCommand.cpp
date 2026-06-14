#include "typeCommand.h"
#include "commandMapping.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

int TypeCommand::execute(const std::vector<std::string>& args) {
  if (args.empty()) return 1;
  std::string commandName {args[0]};

  if (CommandMapping::isBuiltin(commandName)) std::cout << commandName << " is a shell builtin\n";
  else {
    const char* pathVar = std::getenv("PATH");
    
    if (!pathVar) {
      std::cout << commandName << ": not found\n";
      return 0;
    }
    
    std::vector<std::filesystem::path> filenames {getFileNames(pathVar)};
    for (auto& filePath : filenames) {
      if (filePath.filename().string() == commandName) {
        std::cout << commandName << " is " << filePath.string() << '\n';
        return 0;
      }
    }

    std::cout << commandName << ": not found\n";
    return 0;
  }

  return 0;
}
