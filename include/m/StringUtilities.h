#pragma once
#include <iterator>
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
                using std::swap;
                swap(colIt[1], diagonal);
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

    template <class ForwardIt1, class ForwardIt2>
    constexpr bool startsWith(ForwardIt1 start, ForwardIt1 last, ForwardIt2 startPrefix, ForwardIt2 lastPrefix) noexcept {
        for (; start != last && startPrefix != lastPrefix && *start == *startPrefix; ++start, ++startPrefix);
        return startPrefix == lastPrefix;
    }

    template <class T1, class T2>
    constexpr bool startsWith(const T1& s, const T2& prefix) noexcept {
        using std::begin;
        using std::end;
        return startsWith(begin(s), end(s), begin(prefix), end(prefix));
    }

    template <class BiDirIt1, class BiDirIt2>
    constexpr bool endsWith(BiDirIt1 start, BiDirIt1 last, BiDirIt2 startSuffix, BiDirIt2 lastSuffix) noexcept {
        return startsWith(std::reverse_iterator<BiDirIt1>{start}, std::reverse_iterator<BiDirIt1>{last},
                          std::reverse_iterator<BiDirIt2>{startSuffix}, std::reverse_iterator<BiDirIt2>{lastSuffix});
    }

    template <class T1, class T2>
    constexpr bool endsWith(const T1& s, const T2& suffix) noexcept {
        using std::rbegin;
        using std::rend;
        return startsWith(rbegin(s), rend(s), rbegin(suffix), rend(suffix));
    }
}
