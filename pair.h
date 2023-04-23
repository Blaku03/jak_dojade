#ifndef MY_STL_PAIR_H
#define MY_STL_PAIR_H

namespace my_stl {
    template<typename T1, typename T2>
    class pair {
    public:
        T1 first;
        T2 second;

        pair() = default;

        ~pair() = default;

        pair(T1 value_first, T2 value_second);

        pair(const pair &user_pair);

        pair(pair &&pair_move) noexcept;

        pair<T1, T2> &make_pair(T1 first, T2 second);

        bool operator==(const pair &pair_compare) const;

        pair &operator=(const pair &pair_copy);

        pair &operator=(pair &&pair_move) noexcept;
    };


}

#endif //MY_STL_PAIR_H
