#include "scorer.h"
#include "tokenizer.h"
#include <cmath>
#include <unordered_map>
#include <unordered_set>

std::vector<std::pair<int, double>> score_documents(
    const std::string &query,
    const Index &index,
    const std::vector<Document> &documents)
{
    std::vector<std::string> terms = tokenize(query);
    int N = static_cast<int>(documents.size());

    std::unordered_map<int, double> scores;

    for (const std::string &term : terms)
    {
        auto it = index.find(term);
        if (it == index.end())
            continue;

        const std::vector<Posting> &postings = it->second;

        std::unordered_set<int> distinct_docs;
        for (const Posting &p : postings)
            distinct_docs.insert(p.doc_id);
        int df = static_cast<int>(distinct_docs.size());

        for (int doc_id : distinct_docs)
        {
            int raw_count = 0;
            for (const Posting &p : postings)
                if (p.doc_id == doc_id)
                    raw_count++;

            double tf_idf = (1.0 + std::log(raw_count)) * std::log(static_cast<double>(N) / df);
            scores[doc_id] += tf_idf;
        }
    }

    std::vector<std::pair<int, double>> result;
    for (const auto &entry : scores)
        result.push_back(entry);

    return result;
}