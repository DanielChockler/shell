#include "commandMapping.h"
#include "parser.h"
#include <iostream>
#include <string>

std::string getInput() {
  std::string input {};
  std::getline(std::cin, input);
  return input;
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  
  Parser parser;
  CommandMapping mapper;

  while (true) {
    std::cout << "$ ";
    std::string input {getInput()};
    if (input.empty()) continue;
    
    int exitCode = -1;
    CommandInput ci {parser.parse(input)};
    
    if (ci.name == "exit") break;

    bool validCommand {mapper.executeCommand(ci.name, ci.args, exitCode)};

    if (!validCommand) std::cout << ci.name << ": not found\n";
 }
}
