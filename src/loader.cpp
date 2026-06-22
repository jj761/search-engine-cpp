#include "loader.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace fs = std::filesystem;

std::vector<Document> load_documents(const std::string &corpus_path)
{
    std::vector<Document> documents;
    int nextId = 0;
    int failedCount = 0;

    for (const auto &entry : fs::directory_iterator(corpus_path))
    {
        if (!entry.is_regular_file())
        {
            continue;
        }

        std::string filename = entry.path().filename().string();

        // --- Read file content ---
        std::ifstream file(entry.path());
        if (!file.is_open())
        {
            std::cerr << "FAILED to open: " << filename << "\n";
            failedCount++;
            continue;
        }

        std::stringstream ss;
        ss << file.rdbuf();
        std::string content = ss.str();

        // --- Split into lines ---
        std::vector<std::string> lines;
        std::stringstream contentStream(content);
        std::string line;
        while (std::getline(contentStream, line))
        {
            lines.push_back(line);
        }

        // --- Find START/END marker lines ---
        int startLine = -1;
        int endLine = -1;

        for (size_t i = 0; i < lines.size(); i++)
        {
            if (lines[i].rfind("*** START OF", 0) == 0 ||
                lines[i].rfind("***START OF", 0) == 0)
            {
                startLine = i;
            }
            if (lines[i].rfind("*** END OF", 0) == 0 ||
                lines[i].rfind("***END OF", 0) == 0)
            {
                endLine = i;
                break;
            }
        }

        // --- Guard: markers not found ---
        if (startLine == -1 || endLine == -1)
        {
            std::cerr << "FAILED (markers not found): " << filename
                      << " (startLine=" << startLine
                      << ", endLine=" << endLine << ")\n";
            failedCount++;
            continue;
        }

        // --- Guard: nonsensical ordering ---
        if (endLine <= startLine)
        {
            std::cerr << "FAILED (endLine <= startLine): " << filename
                      << " (startLine=" << startLine
                      << ", endLine=" << endLine << ")\n";
            failedCount++;
            continue;
        }

        // --- Slice cleaned content ---
        std::string cleaned;
        for (int i = startLine + 1; i < endLine; i++)
        {
            cleaned += lines[i];
            cleaned += "\n";
        }

        // --- Store as Document ---
        Document doc;
        doc.id = nextId++;
        doc.filename = filename;
        doc.content = cleaned;
        documents.push_back(doc);
    }

    std::cout << "Failed: " << failedCount << "\n";

    return documents;
}