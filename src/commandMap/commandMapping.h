#ifndef CMDMAP
#define CMDMAP

#include "commands.h"
#include "fileHandler.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

class CommandMapping {
private:
  std::unordered_map<std::string, std::unique_ptr<Command>> m_mapping;

public:
  CommandMapping();

  static bool isBuiltin(const std::string& commandName);
  bool executeCommand(const std::string& commandName, const std::vector<std::string>& args, int& exitCode);
  bool executeCommandFile(const std::string& commandName, const std::vector<std::string>& args, int& exitCode) const;
};

#endif

