#ifndef Doremi_STL
#define Doremi_STL

#ifdef USE_USTL
#include <uvector.h>
#include <uctralgo.h>
using namespace ustl;
#else
#include <algorithm>
using namespace std;
#endif

namespace doremi {

template <typename RandomAccessIterator, typename T, typename Compare>
void doremi_unguarded_linear_insert(RandomAccessIterator last, T value, Compare comp)
{
    RandomAccessIterator next = last;
    --next;
    while (comp(value, *next)) {
        *last = *next;
        last = next;
        --next;
    }
    *last = value;
}

template <typename RandomAccessIterator, typename T, typename Compare>
inline void doremi_linear_insert(RandomAccessIterator first,
                            RandomAccessIterator last, T*, Compare comp)
{
    T value = *last;
    if (comp(value, *first)) {
        copy_backward(first, last, last + 1);
        *first = value;
    } else
        doremi_unguarded_linear_insert(last, value);
}

template <typename RandomAccessIterator, typename Compare>
void doremi_insertion_sort(RandomAccessIterator first,
                     RandomAccessIterator last, Compare comp)
{
    if (first == last) return;
    for (RandomAccessIterator i = first + 1; i != last; ++i) {
        typename iterator_traits<RandomAccessIterator>::value_type value = *i;
        if (comp(value, *first)) {
            copy_backward(first, i, i + 1);
            *first = value;
        } else
            doremi_unguarded_linear_insert(i, value, comp);
    }

}

}

#endif
