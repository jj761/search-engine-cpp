#include <iostream>
#include <filesystem>
#include "loader.h"
#include "tokenizer.h"
#include "indexer.h"

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

    // Sanity check: look up a common word
    std::string probe = "the";
    if (index.count(probe))
        std::cout << "Postings for \"" << probe << "\": " << index[probe].size() << "\n";

    return 0;
}