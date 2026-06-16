#include "commandMapping.h"
#include "echoCommand.h"
#include "fileHandler.h"
#include "typeCommand.h"
#include "pwdCommand.h"
#include <cstdlib>
#include <memory>
#include <optional>
#include <string>
#include <unordered_set>
#include <filesystem>
#include <vector>

CommandMapping::CommandMapping() {
  m_mapping["echo"] = std::make_unique<EchoCommand>();
  m_mapping["type"] = std::make_unique<TypeCommand>();
  m_mapping["pwd"]  = std::make_unique<PwdCommand>();
}

bool CommandMapping::isBuiltin(const std::string &commandName) {
  static std::unordered_set<std::string> builtinCommands {"echo", "exit", "type", "pwd"};
  return builtinCommands.contains(commandName);
}

bool CommandMapping::executeCommand(const std::string& commandName, const std::vector<std::string>& args, int& exitCode) {
  auto it = m_mapping.find(commandName);
  if (it == m_mapping.end()) {
    if (executeCommandFile(commandName, args, exitCode)) return true;
    else return false;
  } else {
    exitCode = it->second->execute(args);
    return true;
  }
}

namespace fs = std::filesystem;

bool CommandMapping::executeCommandFile(const std::string& commandName, const std::vector<std::string>& args, int& exitCode) const {
  const char* path = std::getenv("PATH");
  FileHandler fileHandler(path);
  std::optional<fs::directory_entry> file {fileHandler.isCommandInDirectories(commandName)};
  if (file) {
    exitCode = fileHandler.executeCommandFile(*file, args);
    return true;
  } else return false;
}
