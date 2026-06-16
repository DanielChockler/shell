#ifndef CD
#define CD

#include "commands.h"
#include <string>
#include <vector>

class CdCommand : public Command {
private:

public:
  int execute(const std::vector<std::string>& args) override;
};

#endif
