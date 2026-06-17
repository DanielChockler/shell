#include "parser.h"
#include <cstddef>
#include <string>

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
  if (rawInput.empty()) return { };
  
  std::vector<std::string> tokens {};
  auto slow {0uz};
  auto fast {0uz};

  while (slow < rawInput.size()) {
    if (rawInput[slow] == '\'') {
      tokens.push_back(parseSingleQuote(rawInput.substr(slow), slow));
      fast = slow;
      ++slow;
    }

    fast = rawInput.find(delimiter, slow);
    if (fast == std::string::npos) {
      tokens.push_back(std::move(rawInput.substr(slow)));
      break;
    }
    
    // Ignore consecutive delimiters (hello    world -> hello world)
    if (fast == slow) {
      ++fast;
      ++slow;
      continue;
    }
  
    tokens.push_back(std::move(rawInput.substr(slow, fast - slow)));
    slow = fast + 1;
  }

  return tokens;
}

std::string Parser::parseSingleQuote(const std::string& input, size_t& index) const {
  std::string returnStr {};
  returnStr.reserve(input.size());
  
  bool inQuote = false;
  auto i {0uz};

  while (i < input.size()) {
    if (input[i] == '\'') {
      if (i + 1 < input.size() && input[i + 1] == '\'') i += 2;
      else {
        inQuote = !inQuote;
        ++i;
      }
    } else {
      returnStr += input[i];
      ++i;
    }
  }

  index = i;

  return returnStr;
}
