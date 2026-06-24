#include "topk.h"
#include <algorithm>

std::vector<std::pair<int, double>> top_k_results(
    const std::vector<std::pair<int, double>> &scores,
    int k)
{
    std::vector<std::pair<int, double>> sorted = scores;

    std::sort(sorted.begin(), sorted.end(),
              [](const std::pair<int, double> &a, const std::pair<int, double> &b)
              {
                  if (a.second != b.second)
                      return a.second > b.second;
                  return a.first < b.first;
              });

    int limit = std::min(k, static_cast<int>(sorted.size()));
    return std::vector<std::pair<int, double>>(sorted.begin(), sorted.begin() + limit);
}