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
    
    namespace fs = std::filesystem;

    std::vector<fs::directory_entry> files {getFileNames(pathVar)};
    for (auto& file : files) {
      fs::perms filePerms = file.status().permissions();
      if (((filePerms & fs::perms::owner_exec) == fs::perms::none) && ((filePerms & fs::perms::group_exec) == fs::perms::none) && ((filePerms & fs::perms::others_exec) == fs::perms::none)) continue;
      if (file.path().filename().string() == commandName) {
        std::cout << commandName << " is " << file.path().string() << '\n';
        return 0;
      }
    }

    std::cout << commandName << ": not found\n";
    return 0;
  }

  return 0;
}
