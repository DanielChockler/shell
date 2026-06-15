#ifndef FILEHANDLER
#define FILEHANDLER
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class FileHandler {
private:
  std::vector<std::string> m_directories {};

public:
  FileHandler();
  FileHandler(const std::string& path);
  FileHandler(const std::vector<std::string>& directories);

  ~FileHandler();

  std::vector<fs::directory_entry> getFiles() const;
  bool isFileExecutable(const fs::directory_entry& file) const;
  std::optional<fs::directory_entry> isCommandInDirectories(const std::string& commandName) const;
  int executeCommandFile(fs::directory_entry file) const;
};

#endif
