#pragma once
#include <iterator>
#include <initializer_list>

//  for (auto& i : m::reversed({1, 2, 3, 4}))
//      i = 4..3..2..1
//
//  for (auto i : m::enumerate({2, 4, 6, 8})) {
//      i.index = 0..1..2..3
//      i.element = 2..4..6..8
//  }
namespace m {
    namespace detail {
        template <class Iterable>
        class ReversedIterable {
        public:
            template <class T>
            explicit ReversedIterable(T&& iterable) : mIterable{std::forward<T>(iterable)} {}

            auto begin() const { return std::rbegin(mIterable); }
            auto begin()       { return std::rbegin(mIterable); }
            auto   end() const { return std::rend(mIterable); }
            auto   end()       { return std::rend(mIterable); }

        private:
            Iterable mIterable;
        };
    }

    template <class Iterable>
    auto reversed(Iterable&& iterable) {
        return detail::ReversedIterable<Iterable>{std::forward<Iterable>(iterable)};
    }

    template <class T>
    auto reversed(std::initializer_list<T> iterable) {
        return detail::ReversedIterable<std::initializer_list<T>>{std::move(iterable)};
    }

    namespace detail {
        template <class Iterable, class Index>
        class EnumerateIterable {
        public:
            struct Enumerable {
                Index index;
                decltype(*std::begin(std::declval<Iterable>()))& element;
            };

            struct EnumerablePointerProxy {
                Enumerable enumerable;
                Enumerable* operator->() { return &enumerable; }
            };

            class Iterator : public std::iterator<std::input_iterator_tag, Enumerable> {
            public:
                using UnderlyingIterator = decltype(std::begin(std::declval<Iterable>()));

                template <class T>
                Iterator(T&& iterator, Index index) : mIterator{std::forward<T>(iterator)}, mIndex{index} {}

                Enumerable operator*()                    { return {mIndex, *mIterator}; }
                Enumerable operator*() const              { return {mIndex, *mIterator}; }
                EnumerablePointerProxy operator->()       { return {mIndex, *mIterator}; }
                EnumerablePointerProxy operator->() const { return {mIndex, *mIterator}; }

                Iterator& operator++() {
                    ++mIterator;
                    ++mIndex;
                    return *this;
                }

                Iterator operator++(int) {
                    auto ret = *this;
                    ++mIterator;
                    ++mIndex;
                    return ret;
                }

                bool operator==(const Iterator& other) const           { return mIterator == other.mIterator; }
                bool operator==(const UnderlyingIterator& other) const { return mIterator == other; }
                bool operator!=(const Iterator& other) const           { return mIterator != other.mIterator; }
                bool operator!=(const UnderlyingIterator& other) const { return mIterator != other; }

            private:
                UnderlyingIterator mIterator;
                Index              mIndex;
            };

            template <class T>
            explicit EnumerateIterable(T&& iterable, Index index)
                : mIterable{std::forward<T>(iterable)}
                , mIndex{index}
            {}

            auto begin() const { return Iterator{std::begin(mIterable), mIndex}; }
            auto begin()       { return Iterator{std::begin(mIterable), mIndex}; }
            auto   end() const { return std::end(mIterable); }
            auto   end()       { return std::end(mIterable); }

        private:
            Iterable mIterable;
            Index    mIndex;
        };

        template <class T, class = void>
        struct IterableIndexSizeType {
            using type = size_t;
        };

        template <class T>
        struct IterableIndexSizeType<T, std::void_t<typename std::remove_reference_t<T>::size_type>> {
            using type = typename std::remove_reference_t<T>::size_type;
        };

        template <class T>
        using IterableIndexSizeType_t = typename IterableIndexSizeType<T>::type;
    }

    template <class Iterable, class Index = detail::IterableIndexSizeType_t<Iterable>>
    auto enumerate(Iterable&& iterable, Index start = {}) {
        return detail::EnumerateIterable<Iterable, Index>{std::forward<Iterable>(iterable), start};
    }

    template <class T, class Index = detail::IterableIndexSizeType_t<std::initializer_list<T>>>
    auto enumerate(std::initializer_list<T> iterable, Index start = {}) {
        return detail::EnumerateIterable<std::initializer_list<T>, Index>{std::move(iterable), start};
    }
}
