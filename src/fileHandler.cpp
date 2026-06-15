#include "fileHandler.h"
#include "parser.h"
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace fs = std::filesystem;

FileHandler::FileHandler() {}
FileHandler::FileHandler(const std::string& path) {
  Parser parser;
  m_directories = parser.tokenise(path,":");
}
FileHandler::FileHandler(const std::vector<std::string>& directories) : m_directories(directories) {}
FileHandler::~FileHandler() {}

std::vector<fs::directory_entry> FileHandler::getFiles() const {
  std::vector<fs::directory_entry> files {};
  for (const auto& directory : m_directories) {
    if (fs::exists(directory) && fs::is_directory(directory)) {
      for (const auto& file : fs::directory_iterator(directory)) {
        if (file.is_regular_file()) files.push_back(file);
      }
    }
  }

  return files;
}

bool FileHandler::isFileExecutable(const fs::directory_entry& file) const {
  fs::perms filePerms {file.status().permissions()};
  return !((filePerms & fs::perms::owner_exec)  == fs::perms::none && 
       (filePerms & fs::perms::group_exec)  == fs::perms::none &&
       (filePerms & fs::perms::others_exec) == fs::perms::none);
}

std::optional<fs::directory_entry> FileHandler::isCommandInDirectories(const std::string& commandName) const {
  std::vector<fs::directory_entry> files {getFiles()};
  for (auto& file : files) {
    if (file.path().filename().filename() == commandName && isFileExecutable(file))
      return file;
  }

  return { };
}

int FileHandler::executeCommandFile(fs::directory_entry file, const std::vector<std::string>& args) const {
  std::string fullCommand {file.path().string()};
  size_t nameBegin {fullCommand.find_last_of('/')};
  if (nameBegin != std::string::npos) fullCommand = fullCommand.substr(nameBegin + 1);
  fullCommand += " ";

  for (const auto& arg : args) 
    fullCommand += (arg + " ");
  
  return std::system(fullCommand.c_str());
}
