#ifndef PARSER
#define PARSER

#include <string>
#include <vector>
#include <algorithm>
#include <utility>

struct CommandInput {
  std::string name {};
  std::vector<std::string> args {};
};

class Parser {
private:
  std::vector<std::string> tokenise(const std::string& rawInput, const std::string& delimiter);

public:
  Parser() = default;
  ~Parser() = default;

  CommandInput parse(const std::string& rawInput);
};

#endif
