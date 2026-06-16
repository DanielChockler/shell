#include "pwdCommand.h"
#include <filesystem>
#include <string>
#include <vector>
#include <iostream>

namespace fs = std::filesystem;

int PwdCommand::execute(const std::vector<std::string>&) {
  std::cout << fs::current_path().string() << '\n';
  return 0;
}
