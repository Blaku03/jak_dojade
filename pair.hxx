#pragma once

#include "pair.h"

template<typename T1, typename T2>
my_stl::pair<T1, T2>::pair(T1 value_first, T2 value_second) : first(value_first), second(value_second) {}

template<typename T1, typename T2>
my_stl::pair<T1, T2>::pair(const pair<T1, T2> &pair_copy) : first(pair_copy.first), second(pair_copy.second) {}

template<typename T1, typename T2>
my_stl::pair<T1, T2>::pair(pair<T1, T2> &&pair_copy) noexcept : first(pair_copy.first), second(pair_copy.second) {}

template<typename T1, typename T2>
my_stl::pair<T1, T2> &my_stl::pair<T1, T2>::make_pair(T1 first, T2 second) {
    return pair(first, second);
}

template<typename T1, typename T2>
bool my_stl::pair<T1, T2>::operator==(const pair<T1, T2> &pair_compare) const {
    return (pair_compare.first == first && pair_compare.second == second);
}

template<typename T1, typename T2>
my_stl::pair<T1, T2> &my_stl::pair<T1, T2>::operator=(const pair<T1, T2> &pair_copy) {
    first = pair_copy.first;
    second = pair_copy.second;

    return *this;
}

template<typename T1, typename T2>
my_stl::pair<T1, T2> &my_stl::pair<T1, T2>::operator=(pair<T1, T2> &&pair_copy) noexcept {
    first = pair_copy.first;
    second = pair_copy.second;

    return *this;
}