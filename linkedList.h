#pragma once

#include <iostream>

namespace my_stl {
    template<typename T>
    class node {
    public:
        node *next = nullptr;
        node *previous = nullptr;
        T data;

        explicit node(T data) {
            this->data = data;
        }

        ~node() = default;
    };

    template<typename T>
    class linkedList {
    private:
        void copyList(const linkedList &user_list);

        void moveList(linkedList &&user_list) noexcept;

    public:
        node<T> *first = nullptr;
        node<T> *last = nullptr;
        size_t number_of_nodes = 0;

        T *operator[](size_t index) const;

        void push_back(T item_data);

        void push_front(T item_data);

        void pop_index(size_t index);

        linkedList &operator=(const linkedList &user_list);

        linkedList &operator=(linkedList &&user_list) noexcept;

        linkedList() = default;

        linkedList(const linkedList &user_list);

        linkedList(linkedList &&user_list) noexcept;

        ~linkedList();
    };

}
