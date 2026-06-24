#ifndef TOPK_H
#define TOPK_H

#include <vector>
#include <utility>

std::vector<std::pair<int, double>> top_k_results(
    const std::vector<std::pair<int, double>> &scores,
    int k);

#endif