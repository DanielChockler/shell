#include "fileHandler.h"
#include "parser.h"
#include <filesystem>
#include <optional>
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

std::optional<fs::directory_entry> FileHandler::isCommandInDirectories(std::string& commandName) const {
  std::vector<fs::directory_entry> files {getFiles()};
  for (auto& file : files) {
    if (file.path().filename().filename() == commandName && isFileExecutable(file))
      return file;
  }

  return { };
}
