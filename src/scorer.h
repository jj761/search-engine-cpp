#ifndef SCORER_H
#define SCORER_H

#include <string>
#include <vector>
#include <utility>
#include "indexer.h"
#include "loader.h"

std::vector<std::pair<int, double>> score_documents(
    const std::string &query,
    const Index &index,
    const std::vector<Document> &documents);

#endif