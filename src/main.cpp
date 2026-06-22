#include <iostream>
#include "loader.h"
#include "tokenizer.h"
#include <filesystem>

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

    // --- Summary check (mandatory per protocol) ---
    std::cout << "\nDocuments loaded: " << documents.size() << "\n";

    if (!documents.empty())
    {
        size_t minLen = documents[0].content.size();
        size_t maxLen = documents[0].content.size();

        for (const auto &doc : documents)
        {
            minLen = std::min(minLen, doc.content.size());
            maxLen = std::max(maxLen, doc.content.size());
        }

        std::cout << "Min content length: " << minLen << "\n";
        std::cout << "Max content length: " << maxLen << "\n";
    }

    return 0;
}