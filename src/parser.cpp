#include "parser.h"
#include <algorithm>

ParsedQuery parse_query(const std::string &input)
{
    std::string trimmed = input;

    // strip leading whitespace
    trimmed.erase(trimmed.begin(), std::find_if(trimmed.begin(), trimmed.end(),
                                                [](unsigned char c)
                                                { return !std::isspace(c); }));

    // strip trailing whitespace
    trimmed.erase(std::find_if(trimmed.rbegin(), trimmed.rend(),
                               [](unsigned char c)
                               { return !std::isspace(c); })
                      .base(),
                  trimmed.end());

    // detect phrase query: starts and ends with double quotes
    if (trimmed.size() >= 2 && trimmed.front() == '"' && trimmed.back() == '"')
    {
        std::string term = trimmed.substr(1, trimmed.size() - 2);
        return {QueryType::PHRASE, term};
    }

    return {QueryType::KEYWORD, trimmed};
}