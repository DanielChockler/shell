#ifndef PARSER
#define PARSER

#include <cstddef>
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
  std::string parseSingleQuote(const std::string& input, size_t& index) const;

public:
  std::vector<std::string> tokenise(const std::string& rawInput, const std::string& delimiter);

  Parser() = default;
  ~Parser() = default;

  CommandInput parse(const std::string& rawInput);
};

#endif
