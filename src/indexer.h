#ifndef INDEXER_H
#define INDEXER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "loader.h"

struct Posting
{
    int doc_id;
    int position;
};

using Index = std::unordered_map<std::string, std::vector<Posting>>;

Index build_index(const std::vector<Document> &documents);

#endif