#ifndef PHRASE_H
#define PHRASE_H

#include <string>
#include <vector>
#include "indexer.h"

std::vector<int> phrase_search(
    const std::string &phrase,
    const Index &index);

#endif