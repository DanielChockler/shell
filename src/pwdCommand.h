#ifndef PWD
#define PWD

#include "commands.h"
#include <string>
#include <vector>

class PwdCommand : public Command {
private:

public:
  int execute(const std::vector<std::string>&) override;
};

#endif
