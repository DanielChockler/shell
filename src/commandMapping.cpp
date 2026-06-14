#include "commandMapping.h"
#include "echoCommand.h"
#include "typeCommand.h"
#include <memory>
#include <unordered_set>

CommandMapping::CommandMapping() {
  m_mapping["echo"] = std::make_unique<EchoCommand>();
  m_mapping["type"] = std::make_unique<TypeCommand>();
}

bool CommandMapping::isBuiltin(const std::string &commandName) {
  static std::unordered_set<std::string> builtinCommands {"echo", "exit", "type"};
  return builtinCommands.contains(commandName);
}

bool CommandMapping::executeCommand(const std::string& commandName, const std::vector<std::string>& args, int& exitCode) {
  auto it = m_mapping.find(commandName);
  if (it == m_mapping.end()) return false;
  
  exitCode = it->second->execute(args);
  return true;
}
