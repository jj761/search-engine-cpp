#include <iostream>
#include <vector>
#include <utility>
#include "../src/topk.h"

int main()
{
    // Synthetic input — fixed scores, constructed by hand
    // Do NOT call score_documents() here — top-k must be tested in isolation
    std::vector<std::pair<int, double>> scores = {
        {2, 0.9},
        {0, 0.4},
        {1, 0.7},
        {3, 0.7},
        {4, 0.1}};

    // Test 1: k smaller than total results
    std::cout << "=== Test 1: top 3 of 5 ===\n";
    auto r1 = top_k_results(scores, 3);
    for (const auto &p : r1)
        std::cout << "doc " << p.first << " score " << p.second << "\n";
    // Expected:
    // doc 2 score 0.9
    // doc 1 score 0.7
    // doc 3 score 0.7

    // Test 2: k larger than total results
    std::cout << "=== Test 2: top 10 of 5 ===\n";
    auto r2 = top_k_results(scores, 10);
    for (const auto &p : r2)
        std::cout << "doc " << p.first << " score " << p.second << "\n";
    // Expected: all 5, sorted — same order as Test 1 then doc 0 then doc 4

    // Test 3: tie-breaking — docs 1 and 3 both score 0.7, doc 1 should come first
    std::cout << "=== Test 3: tie-breaking check ===\n";
    auto r3 = top_k_results(scores, 5);
    std::cout << "doc at rank 2: " << r3[1].first << " (expected 1)\n";
    std::cout << "doc at rank 3: " << r3[2].first << " (expected 3)\n";

    // Test 4: k = 1
    std::cout << "=== Test 4: top 1 ===\n";
    auto r4 = top_k_results(scores, 1);
    std::cout << "doc " << r4[0].first << " score " << r4[0].second << "\n";
    // Expected: doc 2 score 0.9

    // Test 5: empty input
    std::cout << "=== Test 5: empty input ===\n";
    std::vector<std::pair<int, double>> empty = {};
    auto r5 = top_k_results(empty, 5);
    std::cout << "result size: " << r5.size() << " (expected 0)\n";

    return 0;
}