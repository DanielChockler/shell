#ifndef TYPE
#define TYPE

#include "commands.h"
#include "parser.h"
#include <string>
#include <vector>
#include <filesystem>

class TypeCommand : public Command {
private:
  static std::vector<std::filesystem::path> getFileNames(const std::string& path) {
    std::vector<std::filesystem::path> fileNames {};

    Parser parser;
    std::vector<std::string> directories {parser.tokenise(path, ":")};
    
    for (const auto& directory : directories) {
      for (const auto& file : std::filesystem::directory_iterator(directory)) {
        if (file.is_regular_file()) {
          fileNames.push_back(file.path());
        }
      }
    }

    return fileNames;
  }

public:
  int execute(const std::vector<std::string>& args) override;
};

#endif
