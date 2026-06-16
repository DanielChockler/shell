#ifndef TYPE
#define TYPE

#include "commands.h"
#include "parser.h"
#include <optional>
#include <string>
#include <vector>

class TypeCommand : public Command {
private:

public:
  int execute(const std::vector<std::string>& args) override;
};

#endif
