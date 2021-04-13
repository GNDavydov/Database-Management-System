// Copyright 2021 GNDavydov

#ifndef HOMEWORK_1_SORTING_H
#define HOMEWORK_1_SORTING_H

#include <vector>

template<class It, class Out, class Compare = std::less<>>
Out merge(It first1, It last1, It first2, It last2, Out out,
          Compare cmp = Compare{}) {
    auto next1 = first1;
    auto next2 = first2;
    auto nextOut = out;

    while (next1 != last1 && next2 != last2) {
        if (cmp(*next1, *next2)) {
            *nextOut = *next1;
            ++next1;
        } else {
            *nextOut = *next2;
            ++next2;
        }
        ++nextOut;
    }

    while (next1 != last1) {
        *nextOut = *next1;
        ++next1;
        ++nextOut;
    }

    while (next2 != last2) {
        *nextOut = *next2;
        ++next2;
        ++nextOut;
    }

    return out;
}

template<class It, class Out, class Compare = std::less<>>
Out merge_sort(It first, It last, Out out, Compare cmp = Compare{}) {
    if (last - first > 2) {
        std::vector<typename std::iterator_traits<It>::value_type> buf(last -
                                                                       first);
        const size_t middle = (last - first) / 2;

        merge_sort(first, first + middle, buf.begin(), cmp);
        merge_sort(first + middle, last, buf.begin() + middle, cmp);
        merge(buf.begin(), buf.begin() + middle, buf.begin() + middle, buf.end(),
              out, cmp);

    } else if (last - first == 2) {
        if (cmp(*first, *(first + 1))) {
            *out = *first;
            *(out + 1) = *(first + 1);
        } else {
            *out = *(first + 1);
            *(out + 1) = *first;
        }
    } else {
        *out = *first;
    }

    return out;
}

#endif //HOMEWORK_1_SORTING_H
