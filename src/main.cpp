#include <iostream>
#include <filesystem>
#include "loader.h"
#include "tokenizer.h"
#include "indexer.h"
#include "scorer.h"
#include "topk.h"

int main()
{
    std::vector<Document> documents;
    try
    {
        documents = load_documents("../corpus");
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Filesystem error: " << e.what() << "\n";
        return 1;
    }

    std::cout << "Documents loaded: " << documents.size() << "\n";

    Index index = build_index(documents);

    std::cout << "Unique terms in index: " << index.size() << "\n";

    std::string query = "white whale";
    std::cout << "\nQuery: \"" << query << "\"\n";

    auto scores = score_documents(query, index, documents);
    auto results = top_k_results(scores, 5);

    std::cout << "Top " << results.size() << " results:\n";
    for (const auto &p : results)
        std::cout << "  doc " << p.first
                  << " (" << documents[p.first].filename << ")"
                  << "  score " << p.second << "\n";

    return 0;
}