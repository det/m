#pragma once
#include <string_view>
#include <numeric>
#include <vector>
#include <utility>

namespace m {
    inline size_t levenshteinDistance(const std::string_view &left, const std::string_view &right)
    {
        auto column = std::vector<size_t>(right.size() + 1);
        std::iota(column.begin(), column.end(), 0); // fill column with 0..1..2..3...
        
        for (size_t i = 0; i < left.size(); ++i) {
            column[0] = i + 1;
            auto diagonal = i;
            for (size_t j = 0; j < right.size(); ++j) {
                diagonal = std::min({column[j] + 1, column[j + 1] + 1, diagonal + (left[i] != right[j])});
                std::swap(column[j + 1], diagonal);
            }
        }
        
        return column.back();
    }
}
