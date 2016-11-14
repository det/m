#pragma once
#include <iterator>
#include <random>

namespace m {
    // Selects n unique elements from the sequence [first; last) such that each possible sample has
    // equal probability of appearance, and writes those selected elements into the output iterator
    // out. The elements which are chosen are random, but the order in which they appear in out may
    // be partially or entirely ordered by the order they appeared in the input range. O(n).
    //
    // first, last  -  The input range. PopulationIt must meet the requirements of InputIterator.
    //         out  -  The output iterator where the samples are written. Must not be in the range
    //                 [first;last). SampleIt must meet the requirements of OutputIterator and
    //                 RandomAccessIterator.
    //           n  -  The number of samples to make. Must be less than the input range length.
    //           g  -  The random number generator used as the source of randomness.
    template <typename PopulationIt, typename SampleIt, typename UniformRandomBitGenerator>
    SampleIt UniqueSample(PopulationIt first, PopulationIt last,
                          SampleIt out,
                          typename std::iterator_traits<SampleIt>::difference_type n,
                          UniformRandomBitGenerator&& g)
    {
        using DifferenceType = typename std::iterator_traits<SampleIt>::difference_type;

        for (auto i = DifferenceType{0}; i < n; ++i, ++first) {
            out[i] = *first;
        }

        for (auto count = n; first != last; ++first, ++count) {
            auto i = std::uniform_int_distribution<DifferenceType>(0, count)(g);
            if (i < n) {
                out[i] = *first;
            }
        }

        return std::next(out, n);
    }

    // The same as UniqueSample except it fills the output range with iterators to elements in the
    // input range instead of values from the input range.
    template <typename PopulationIt, typename SampleIt, typename UniformRandomBitGenerator>
    SampleIt UniqueSampleIterators(PopulationIt first, PopulationIt last,
                                   SampleIt out,
                                   typename std::iterator_traits<SampleIt>::difference_type n,
                                   UniformRandomBitGenerator&& g)
    {
        using DifferenceType = typename std::iterator_traits<SampleIt>::difference_type;

        for (auto i = DifferenceType{0}; i < n; ++i, ++first) {
            out[i] = first;
        }

        for (auto count = n; first != last; ++first, ++count) {
            auto i = std::uniform_int_distribution<DifferenceType>(0, count)(g);
            if (i < n) {
                out[i] = first;
            }
        }

        return std::next(out, n);
    }
}
