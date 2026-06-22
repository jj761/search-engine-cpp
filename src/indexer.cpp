#include "indexer.h"
#include "tokenizer.h"

Index build_index(const std::vector<Document> &documents)
{
    Index index;
    for (const auto &doc : documents)
    {
        auto tokens = tokenize(doc.content);
        for (int i = 0; i < (int)tokens.size(); i++)
        {
            index[tokens[i]].push_back({doc.id, i});
        }
    }
    return index;
}