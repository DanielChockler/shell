#include <iostream>
#include <string>
#include <algorithm>

void echo(const std::string&);

std::string getInput() {
  std::string command {};
  std::getline(std::cin, command);
  return command;
}

std::string getCommand(const std::string& line) {
  auto it {std::find_if(line.begin(), line.end(), [](char a) { return (a == ' '); } )};

  return std::string {line.begin(), it};
}

bool processCommand(const std::string& command, const std::string& line) {
  if (command == "echo") {
    echo(line);
    return true;
  }
  
  return false;
}

void echo(const std::string& s) {
  if (s.length() > static_cast<std::size_t>(5)) std::cout << s.substr(5) << '\n';
  else std::cout << '\n';
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (true) {
    std::cout << "$ ";
    std::string input {getInput()};
    std::string command {getCommand(input)};
  
    if (command == "exit") break;
    if (!processCommand(command, input)) std::cout << command << ": command not found\n";
  }
}
