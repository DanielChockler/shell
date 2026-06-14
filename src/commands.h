#ifndef COMMANDS
#define COMMANDS

#include <string>
#include <memory>
#include <vector>

class Command {
public:
  virtual ~Command() = default;

  virtual int execute(const std::vector<std::string>& args) = 0;
};

#endif
