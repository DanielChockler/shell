#ifndef CMDMAP
#define CMDMAP

#include "commands.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

class CommandMapping {
private:
  std::unordered_map<std::string, std::unique_ptr<Command>> m_mapping;

public:
  CommandMapping();

  bool executeCommand(const std::string& commandName, const std::vector<std::string>& args, int& exitCode);
};

#endif

