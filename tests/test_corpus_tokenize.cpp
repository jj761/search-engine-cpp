#include "../src/loader.h"
#include "../src/tokenizer.h"
#include <iostream>
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

    if (documents.empty())
    {
        std::cerr << "No documents loaded — nothing to tokenize.\n";
        return 1;
    }

    size_t totalTokens = 0;
    size_t minTokens = SIZE_MAX;
    size_t maxTokens = 0;
    std::string minFile, maxFile;

    for (const auto &doc : documents)
    {
        auto tokens = tokenize(doc.content);
        size_t count = tokens.size();

        totalTokens += count;

        if (count < minTokens)
        {
            minTokens = count;
            minFile = doc.filename;
        }
        if (count > maxTokens)
        {
            maxTokens = count;
            maxFile = doc.filename;
        }
    }

    std::cout << "Documents tokenized: " << documents.size() << "\n";
    std::cout << "Total tokens (all docs): " << totalTokens << "\n";
    std::cout << "Min tokens: " << minTokens << " (" << minFile << ")\n";
    std::cout << "Max tokens: " << maxTokens << " (" << maxFile << ")\n";

    return 0;
}