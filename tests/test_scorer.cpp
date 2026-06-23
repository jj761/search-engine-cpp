#include "../src/scorer.h"
#include "../src/indexer.h"
#include "../src/loader.h"
#include <iostream>

int main()
{
    // Synthetic corpus:
    // Doc 0: "cat sat"
    // Doc 1: "cat cat dog"
    // Doc 2: "dog ran"
    std::vector<Document> documents = {
        {0, "doc0.txt", "cat sat"},
        {1, "doc1.txt", "cat cat dog"},
        {2, "doc2.txt", "dog ran"}};

    Index index;
    index["cat"] = {{0, 0}, {1, 0}, {1, 1}};
    index["sat"] = {{0, 1}};
    index["dog"] = {{1, 2}, {2, 0}};
    index["ran"] = {{2, 1}};

    std::cout << "Test 1: query \"cat\"" << std::endl;
    auto results = score_documents("cat", index, documents);
    for (const auto &r : results)
        std::cout << "doc_id=" << r.first << " score=" << r.second << std::endl;
    std::cout << "Expected: doc_id=0 score~0.405465, doc_id=1 score~0.686303, doc 2 absent" << std::endl;

    std::cout << "Test 2: query \"dog\"" << std::endl;
    results = score_documents("dog", index, documents);
    for (const auto &r : results)
        std::cout << "doc_id=" << r.first << " score=" << r.second << std::endl;
    std::cout << "Expected: doc_id=1 score~0.405465, doc_id=2 score~0.405465 (symmetric: df=2, raw_count=1 both)" << std::endl;

    std::cout << "Test 3: query \"nonexistent\"" << std::endl;
    results = score_documents("nonexistent", index, documents);
    std::cout << "Result count: " << results.size() << " (expected: 0)" << std::endl;

    std::cout << "Test 4: query \"cat dog\" (multi-term, sums contributions)" << std::endl;
    results = score_documents("cat dog", index, documents);
    for (const auto &r : results)
        std::cout << "doc_id=" << r.first << " score=" << r.second << std::endl;
    std::cout << "Expected: doc0~0.405465 (cat only), doc1~0.686303+0.405465=1.091768 (both), doc2~0.405465 (dog only)" << std::endl;

    return 0;
}