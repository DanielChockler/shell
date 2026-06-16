#include "cdCommand.h"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <system_error>
#include <vector>

namespace fs = std::filesystem;

int CdCommand::execute(const std::vector<std::string>& args) {
  if (args.size() > 1) return 1;

  std::string targetDir;
  if (args.size() > 0) targetDir = args[0];
  if (targetDir == "~" || (args.size() == 0)) targetDir = getHomeDir();

  std::error_code ec;

  fs::current_path(targetDir, ec);

  if (ec) {
    std::cout << "cd: " << targetDir << ": No such file or directory\n";
    return 1;
  }

  return 0;
}

std::string CdCommand::getHomeDir() const {
  const char* homeDir {getenv("HOME")};
  return homeDir;
}
