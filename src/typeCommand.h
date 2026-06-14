#ifndef TYPE
#define TYPE

#include "commands.h"
#include "parser.h"
#include <string>
#include <vector>
#include <filesystem>

class TypeCommand : public Command {
private:
  static std::vector<std::filesystem::directory_entry> getFileNames(const std::string& path) {
    std::vector<std::filesystem::directory_entry> files {};

    Parser parser;
    std::vector<std::string> directories {parser.tokenise(path, ":")};
    
    for (const auto& directory : directories) {
      if (std::filesystem::exists(directory) && std::filesystem::is_directory(directory)) {
        for (const auto& file : std::filesystem::directory_iterator(directory)) {
          if (file.is_regular_file()) {
            files.push_back(file);
          }
        }
      }
    }

    return files;
  }

public:
  int execute(const std::vector<std::string>& args) override;
};

#endif
