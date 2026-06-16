#include "typeCommand.h"
#include "commandMapping.h"
#include "fileHandler.h"
#include <cstdlib>
#include <optional>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

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

    FileHandler fileHandler(pathVar);
    std::optional<fs::directory_entry> commandFile {fileHandler.isCommandInDirectories(commandName)};

    if (commandFile) 
      std::cout << commandName << " is " << commandFile->path().string() << '\n';
    else
      std::cout << commandName << ": not found\n";
  }

  return 0;
 }
