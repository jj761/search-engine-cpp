#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <vector>

struct Document
{
    int id;
    std::string filename;
    std::string content;
};

std::vector<Document> load_documents(const std::string &corpus_path);

#endif