#include <iostream>
#include <vector>
#include "../src/phrase.h"
#include "../src/indexer.h"
#include "../src/loader.h"
#include "../src/tokenizer.h"

// helper: build a minimal index from hand-crafted documents
Index build_test_index(const std::vector<Document> &docs)
{
    return build_index(docs);
}

void print_results(const std::vector<int> &results)
{
    if (results.empty())
    {
        std::cout << "no matches\n";
        return;
    }
    for (int id : results)
        std::cout << "doc " << id << "\n";
}

int main()
{
    // synthetic corpus — bypasses loader entirely
    std::vector<Document> docs = {
        {0, "doc0.txt", "the white whale swam away"},
        {1, "doc1.txt", "white whale hunting is dangerous"},
        {2, "doc2.txt", "the whale was white and large"},
        {3, "doc3.txt", "captain ahab hunted the whale"},
        {4, "doc4.txt", "white and whale are separate here"}};

    Index index = build_test_index(docs);

    // Test 1: phrase present in multiple docs
    std::cout << "=== Test 1: \"white whale\" ===\n";
    print_results(phrase_search("white whale", index));
    // Expected: doc 0, doc 1 (adjacent in both)
    // doc 2: "whale was white" — white and whale not adjacent in correct order
    // doc 4: "white and whale" — not adjacent

    // Test 2: phrase present in only one doc
    std::cout << "=== Test 2: \"the white whale\" ===\n";
    print_results(phrase_search("the white whale", index));
    // Expected: doc 0 only

    // Test 3: phrase not present anywhere
    std::cout << "=== Test 3: \"white shark\" ===\n";
    print_results(phrase_search("white shark", index));
    // Expected: no matches

    // Test 4: single word — behaves like a single-term lookup
    std::cout << "=== Test 4: \"whale\" ===\n";
    print_results(phrase_search("whale", index));
    // Expected: doc 0, doc 1, doc 2, doc 3, doc 4 (all contain whale)

    // Test 5: term exists but second term missing from index entirely
    std::cout << "=== Test 5: \"whale dragon\" ===\n";
    print_results(phrase_search("whale dragon", index));
    // Expected: no matches

    // Test 6: empty phrase
    std::cout << "=== Test 6: empty phrase ===\n";
    print_results(phrase_search("", index));
    // Expected: no matches

    return 0;
}