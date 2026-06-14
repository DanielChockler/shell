#ifndef TYPE
#define TYPE

#include "commands.h"
#include <string>
#include <vector>

class TypeCommand : public Command {
public:
  int execute(const std::vector<std::string>& args) override;
};

#endif
