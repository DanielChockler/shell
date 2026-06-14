#ifndef TYPE
#define TYPE

#include "commands.h"
#include "parser.h"
#include <optional>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class TypeCommand : public Command {
private:
  static std::vector<std::filesystem::directory_entry> getFiles(const std::string& path);
  static bool isExecutableFile(const std::filesystem::perms& filePerms);
  static std::optional<fs::directory_entry> isCommandInPath(std::string& commandName, const char* path);

public:
  int execute(const std::vector<std::string>& args) override;
};

#endif
