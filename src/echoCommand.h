#ifndef ECHO
#define ECHO

#include "commands.h"
#include <vector>
#include <string>

class EchoCommand : public Command {
public:
  EchoCommand() = default;

  ~EchoCommand() = default;

  int execute(const std::vector<std::string>& args) override;
};

#endif
