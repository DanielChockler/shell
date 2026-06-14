#include "commandMapping.h"
#include "echoCommand.h"
#include <memory>

CommandMapping::CommandMapping() {
  m_mapping["echo"] = std::make_unique<EchoCommand>();
}

bool CommandMapping::executeCommand(const std::string& commandName, const std::vector<std::string>& args, int& exitCode) {
  auto it = m_mapping.find(commandName);
  if (it == m_mapping.end()) return false;
  
  exitCode = it->second->execute(args);
  return true;
}
