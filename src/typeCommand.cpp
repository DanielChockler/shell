#include "typeCommand.h"
#include "commandMapping.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

 namespace fs = std::filesystem;

std::vector<std::filesystem::directory_entry> TypeCommand::getFiles(const std::string& path) {
  std::vector<std::filesystem::directory_entry> files {};

  Parser parser;
  std::vector<std::string> directories {parser.tokenise(path, ":")};
    
  for (const auto& directory : directories) {
    if (std::filesystem::exists(directory) && std::filesystem::is_directory(directory)) {
      for (const auto& file : std::filesystem::directory_iterator(directory)) {
        if (file.is_regular_file()) {
          files.push_back(file);
        }
     }
    }
  }
  return files;
}

bool TypeCommand::isExecutableFile(const fs::perms& filePerms) {
  return !((filePerms & fs::perms::owner_exec)  == fs::perms::none && 
       (filePerms & fs::perms::group_exec)  == fs::perms::none &&
       (filePerms & fs::perms::others_exec) == fs::perms::none);
}

std::optional<fs::directory_entry> TypeCommand::isCommandInPath(std::string& commandName, const char* path) {
  std::vector<fs::directory_entry> files {getFiles(path)};
  for (auto& file : files) {
    if (file.path().filename().string() == commandName && isExecutableFile(file.status().permissions())) return file;
  }

  return {};
}

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

    std::optional<fs::directory_entry> commandFile {isCommandInPath(commandName, pathVar)};
    if (commandFile) 
      std::cout << commandName << " is " << commandFile->path().string() << '\n';
    else
      std::cout << commandName << ": not found\n";
  }

  return 0;
 }
