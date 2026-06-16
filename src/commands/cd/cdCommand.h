#ifndef CD
#define CD

#include "commands.h"
#include <string>
#include <vector>

class CdCommand : public Command {
private:
  std::string getHomeDir() const;

public:
  int execute(const std::vector<std::string>& args) override;
};

#endif
