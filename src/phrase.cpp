#include "phrase.h"
#include "tokenizer.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

std::vector<int> phrase_search(
    const std::string &phrase,
    const Index &index)
{
    std::vector<std::string> terms = tokenize(phrase);

    if (terms.empty())
        return {};

    // collect doc_ids that contain the first term
    auto it = index.find(terms[0]);
    if (it == index.end())
        return {};

    // map doc_id -> positions for first term
    std::unordered_map<int, std::vector<int>> candidate_positions;
    for (const Posting &p : it->second)
        candidate_positions[p.doc_id].push_back(p.position);

    // for each subsequent term, narrow candidates
    for (int t = 1; t < static_cast<int>(terms.size()); t++)
    {
        auto it2 = index.find(terms[t]);
        if (it2 == index.end())
            return {};

        // build position map for this term
        std::unordered_map<int, std::vector<int>> current_positions;
        for (const Posting &p : it2->second)
            current_positions[p.doc_id].push_back(p.position);

        // keep only docs where this term follows the previous term
        std::unordered_map<int, std::vector<int>> next_candidates;
        for (const auto &entry : candidate_positions)
        {
            int doc_id = entry.first;
            if (current_positions.find(doc_id) == current_positions.end())
                continue;

            const std::vector<int> &prev_pos = entry.second;
            const std::vector<int> &curr_pos = current_positions[doc_id];

            // check if any position in curr_pos == any position in prev_pos + t
            std::vector<int> valid_positions;
            for (int pos : prev_pos)
            {
                int expected = pos + 1;
                if (std::find(curr_pos.begin(), curr_pos.end(), expected) != curr_pos.end())
                    valid_positions.push_back(expected);
            }

            if (!valid_positions.empty())
                next_candidates[doc_id] = valid_positions;
        }

        candidate_positions = next_candidates;
    }

    std::vector<int> result;
    for (const auto &entry : candidate_positions)
        result.push_back(entry.first);

    std::sort(result.begin(), result.end());
    return result;
}