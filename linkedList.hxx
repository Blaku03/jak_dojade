#pragma once

#include "linkedList.h"

template<typename T>
void my_stl::linkedList<T>::copyList(const linkedList &user_list) {
    node<T> *current_node = user_list.first;

    if (this->first != nullptr) {
        delete this->first;
    }
    first = nullptr;

    while (current_node != nullptr) {
        this->push_back(current_node->data);
        current_node = current_node->next;
    }
}

template<typename T>
void my_stl::linkedList<T>::moveList(linkedList &&user_list) noexcept {

    this->first = user_list.first;
    this->last = user_list.last;
    this->number_of_nodes = user_list.number_of_nodes;

    user_list.first = nullptr;
    user_list.last = nullptr;
    user_list.number_of_nodes = 0;
}

template<typename T>
T *my_stl::linkedList<T>::operator[](size_t index) const {
    if (first == nullptr) return nullptr;

    node<T> *current_node = first;
    for (int i = 0; i < index; i++) {
        if (current_node == nullptr) return nullptr;
        current_node = current_node->next;
    }

    return &current_node->data;
}

template<typename T>
void my_stl::linkedList<T>::push_back(T item_data) {

    //push back in linked list
    auto *new_node = new node<T>(item_data);
    if (first == nullptr) {
        first = new_node;
        last = new_node;
    } else {
        last->next = new_node;
        new_node->previous = last;
        last = new_node;
    }
    number_of_nodes++;
}

template<typename T>
void my_stl::linkedList<T>::push_front(T item_data) {

    //push front in linked list
    auto *new_node = new node<T>(item_data);
    if (first == nullptr) {
        first = new_node;
        last = new_node;
    } else {
        first->previous = new_node;
        new_node->next = first;
        first = new_node;
    }
    number_of_nodes++;
}

template<typename T>
void my_stl::linkedList<T>::pop_index(size_t index) {

    //pop index in linked list
    if (first == nullptr) return;

    node<T> *current_node = first;

    //iterate to index
    for (int i = 0; i < index; i++) {
        if (current_node == nullptr) return;
        current_node = current_node->next;
    }

    if (current_node == first) {
        if (number_of_nodes == 1) {
            first = nullptr;
            delete current_node;
            number_of_nodes--;
            return;
        }
        first = current_node->next;
        first->previous = nullptr;
    } else if (current_node == last) {
        last = current_node->previous;
        last->next = nullptr;
    } else {
        current_node->previous->next = current_node->next;
        current_node->next->previous = current_node->previous;
    }

    delete current_node;
    number_of_nodes--;
}

template<typename T>
my_stl::linkedList<T> &my_stl::linkedList<T>::operator=(const linkedList &user_list) {
    if (this == &user_list) return *this;
    copyList(user_list);
    return *this;
}

template<typename T>
my_stl::linkedList<T> &my_stl::linkedList<T>::operator=(linkedList &&user_list) noexcept {
    moveList(std::move(user_list));
    return *this;
}

template<typename T>
my_stl::linkedList<T>::linkedList(const linkedList &user_list) {
    copyList(user_list);
}

template<typename T>
my_stl::linkedList<T>::linkedList(linkedList &&user_list) noexcept {
    moveList(std::move(user_list));
}

template<typename T>
my_stl::linkedList<T>::~linkedList<T>() {
    while (first != nullptr) {
        node<T> *temp = first;
        first = first->next;
        delete temp;
    }
}
