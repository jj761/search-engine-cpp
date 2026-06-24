#ifndef PARSER_H
#define PARSER_H

#include <string>

enum class QueryType
{
    KEYWORD,
    PHRASE
};

struct ParsedQuery
{
    QueryType type;
    std::string term;
};

ParsedQuery parse_query(const std::string &input);

#endif