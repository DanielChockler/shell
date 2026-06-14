#include "parser.h"

CommandInput Parser::parse(const std::string& rawInput) {
  CommandInput ci;
  auto commandStartIt {std::find_if(rawInput.begin(), rawInput.end(), [](char c) { return c != ' '; } )};
  if (commandStartIt == rawInput.end()) return ci;

  auto commandEndIt {std::find(commandStartIt, rawInput.end(), ' ')};
  ci.name = std::string {commandStartIt, commandEndIt};
  if (commandEndIt == rawInput.end()) return ci;

  ci.args = tokenise(std::string {commandEndIt + 1, rawInput.end()}, " ");

  return ci;
}

std::vector<std::string> Parser::tokenise(const std::string& rawInput, const std::string& delimiter) {
  if (delimiter.empty()) return std::vector<std::string> {rawInput};
  std::vector<std::string> tokens {};
  auto slow {0uz};
  auto fast {0uz};

  while (slow < rawInput.size()) {
    fast = rawInput.find(delimiter, slow);
    if (fast == std::string::npos) {
      tokens.push_back(std::move(rawInput.substr(slow)));
      break;
    }
  
    tokens.push_back(std::move(rawInput.substr(slow, fast - slow)));
    slow = fast + 1;
  }

  return tokens;
}
