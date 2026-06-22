#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

std::string normalize_quotes(const std::string &text);
std::vector<std::string> tokenize(const std::string &text);

#endif