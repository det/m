#pragma once
#include <string_view>
#include <numeric>
#include <vector>
#include <utility>

namespace m {
    template <class ForwardIt1, class ForwardIt2>
    size_t levenshteinDistance(ForwardIt1 start1, ForwardIt1 last1, ForwardIt2 start2, ForwardIt2 last2) {
        auto column = std::vector<size_t>(std::distance(start2, last2) + 1);
        std::iota(column.begin(), column.end(), 0); // fill column with 0..1..2..3...
        
        for (auto i = start1; i != last1; ++i) {
            auto colIt = column.begin();
            auto diagonal = (*colIt)++;
            for (auto j = start2; j != last2; ++j, ++colIt) {
                diagonal = std::min({*colIt + 1, colIt[1] + 1, diagonal + (*i != *j)});
                std::swap(colIt[1], diagonal);
            }
        }

        return column.back();
    }
                                          
    template <class T1, class T2>
    size_t levenshteinDistance(const T1& left, const T2& right) {
        using std::begin;
        using std::end;
        return levenshteinDistance(begin(left), end(left), begin(right), end(right));
    }
}
