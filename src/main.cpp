#include <iostream>
#include <filesystem>
#include "loader.h"
#include "tokenizer.h"
#include "indexer.h"
#include "scorer.h"
#include "topk.h"
#include "parser.h"
#include "phrase.h"

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
    std::cout << "\nEnter a query (or 'quit' to exit):\n";

    std::string input;
    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "quit")
            break;

        ParsedQuery pq = parse_query(input);

        if (pq.term.empty())
        {
            std::cout << "Empty query, try again.\n";
            continue;
        }

        if (pq.type == QueryType::PHRASE)
        {
            std::vector<int> matches = phrase_search(pq.term, index);
            if (matches.empty())
            {
                std::cout << "No results found.\n";
                continue;
            }
            std::cout << "Phrase matches (" << matches.size() << " docs):\n";
            for (int id : matches)
                std::cout << "  doc " << id
                          << " (" << documents[id].filename << ")\n";
            continue;
        }

        auto scores = score_documents(pq.term, index, documents);
        auto results = top_k_results(scores, 10);

        if (results.empty())
        {
            std::cout << "No results found.\n";
            continue;
        }

        std::cout << "Top " << results.size() << " results:\n";
        for (const auto &p : results)
            std::cout << "  doc " << p.first
                      << " (" << documents[p.first].filename << ")"
                      << "  score " << p.second << "\n";
    }

    return 0;
}