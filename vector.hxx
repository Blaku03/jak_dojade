#pragma once

#include "vector.h"

template<typename T>
void my_stl::vector<T>::expand_twice_the_size() {
    //Doubling the size of main buffer
    main_buffer = copy_array(main_buffer, current_size, true);
    current_size *= 2;
}

template<typename T>
T *my_stl::vector<T>::copy_array(T *pointer_to_array_that_should_be_copied, size_t size_of_array, bool double_size) {
    T *copied_array = new T[double_size ? size_of_array * 2 : size_of_array];

    for (unsigned int i = 0; i < size_of_array; i++) {
        *(copied_array + i) = *(pointer_to_array_that_should_be_copied + i);
    }

    return copied_array;
}

template<typename T>
bool my_stl::vector<T>::enough_buffer_space(size_t space_to_add) const {
    return space_to_add + number_of_elements < current_size;
}

template<typename T>
void my_stl::vector<T>::copy_vector(const vector &user_vector) {
    if (main_buffer) delete[] main_buffer;

    main_buffer = copy_array(user_vector.main_buffer, user_vector.current_size, false);
    number_of_elements = user_vector.number_of_elements;
    current_size = user_vector.current_size;
}

template<typename T>
void my_stl::vector<T>::move_vector(vector &&user_vector) noexcept {
    main_buffer = user_vector.main_buffer;
    user_vector.main_buffer = nullptr;
    number_of_elements = user_vector.number_of_elements;
    current_size = user_vector.current_size;
}

template<typename T>
my_stl::vector<T>::vector() {
    current_size = 11;
    main_buffer = new T[current_size];
    number_of_elements = 0;
}

template<typename T>
my_stl::vector<T>::vector(size_t size_of_vector) : current_size(size_of_vector) {
    main_buffer = new T[current_size];
    number_of_elements = 0;
}

template<typename T>
my_stl::vector<T>::vector(const vector<T> &user_vector) {
    copy_vector(user_vector);
}

template<typename T>
my_stl::vector<T>::vector(vector<T> &&user_vector) noexcept {
    move_vector(std::move(user_vector));
}

template<typename T>
my_stl::vector<T>::~vector() {
    if (main_buffer) {
        delete[] main_buffer;
    }
}

template<typename T>
my_stl::vector<T> &my_stl::vector<T>::push_back(const T &user_value) {
    //Check if array isn't too small
    if (current_size <= number_of_elements) expand_twice_the_size();

    //Add user's value to array
    *(main_buffer + number_of_elements) = user_value;
    number_of_elements++;
    return *this;
}

template<typename T>
my_stl::vector<T> &my_stl::vector<T>::push_back(const T *user_arr, size_t size_of_user_arr) {
    while (!enough_buffer_space(size_of_user_arr)) expand_twice_the_size();

    for (int i = 0; i < size_of_user_arr; i++) {
        *(main_buffer + number_of_elements) = *(user_arr + i);
        number_of_elements++;
    }

    return *this;
}

template<typename T>
my_stl::vector<T> &my_stl::vector<T>::push_back(const vector<T> &user_vector) {
    //Add it to variable to not call method all the time
    size_t user_vector_size = user_vector.size();

    while (!enough_buffer_space(user_vector_size)) expand_twice_the_size();

    for (int i = 0; i < user_vector_size; i++) {
        *(main_buffer + number_of_elements) = user_vector.i_element(i);
        number_of_elements++;
    }

    return *this;
}

template<typename T>
my_stl::vector<T> &my_stl::vector<T>::push_back(vector<T> &&user_vector) {
    //Add it to variable to not call method all the time
    size_t user_vector_size = user_vector.size();

    while (!enough_buffer_space(user_vector_size)) expand_twice_the_size();

    for (int i = 0; i < user_vector_size; i++) {
        *(main_buffer + number_of_elements) = user_vector.i_element(i);
        number_of_elements++;
    }

    return *this;
}

template<typename T>
void my_stl::vector<T>::pop() {
    if (number_of_elements > 0) number_of_elements--;
}

template<typename T>
void my_stl::vector<T>::pop_index(size_t index_of_element) {

    if (index_of_element < number_of_elements) {
        T *helper_buffer = new T[current_size];
        T popped_element = main_buffer[index_of_element];

        for (size_t i = 0; i < index_of_element; i++) {
            *(helper_buffer + i) = *(main_buffer + i);
        }

        for (size_t i = index_of_element + 1; i < number_of_elements; i++) {
            *(helper_buffer + i - 1) = *(main_buffer + i);
        }

        number_of_elements--;
        delete[] main_buffer;
        main_buffer = helper_buffer;
    }
}

template<typename T>
void my_stl::vector<T>::pop_front() {
    if (number_of_elements == 0) return;

    T *helper_buffer = new T[current_size];
    T popped_element = main_buffer[0];

    for (int i = 1; i < number_of_elements; i++) {
        *(helper_buffer + i - 1) = *(main_buffer + i);
    }

    number_of_elements--;
    delete[] main_buffer;
    main_buffer = helper_buffer;
}

template<typename T>
void my_stl::vector<T>::shrink_to_fit() {
    T *helper_buffer = copy_array(main_buffer, number_of_elements, false);
    delete[] main_buffer;

    main_buffer = helper_buffer;
    current_size = number_of_elements;
}

template<typename T>
void my_stl::vector<T>::clear() {
    if (main_buffer) delete[] main_buffer;
    current_size = 11;
    main_buffer = new T[current_size];
    number_of_elements = 0;
}

template<typename T>
T &my_stl::vector<T>::i_element(size_t index, bool safe_mode) {
    if (index < number_of_elements || safe_mode) return main_buffer[index];
    std::cout << "ERROR: INDEX GIVEN IS NOT WITHIN THE VECTOR\n";
    exit(99);
}

template<typename T>
T &my_stl::vector<T>::operator[](size_t index) {
    return i_element(index);
}

template<typename T>
const T &my_stl::vector<T>::i_element(size_t index, bool safe_mode) const {
    if (index < number_of_elements || safe_mode) return main_buffer[index];
    std::cout << "ERROR: INDEX GIVEN IS NOT WITHIN THE VECTOR\n";
    exit(99);
}

template<typename T>
const T &my_stl::vector<T>::operator[](size_t index) const {
    return i_element(index);
}

template<typename T>
my_stl::vector<T> &my_stl::vector<T>::operator=(const vector &user_vector) {
    if (this == &user_vector) return *this;

    copy_vector(user_vector);

    return *this;
}

template<typename T>
my_stl::vector<T> &my_stl::vector<T>::operator=(vector &&user_vector) noexcept {
    move_vector(std::move(user_vector));

    return *this;
}

template<typename T>
my_stl::vector<T> &my_stl::vector<T>::operator+(const vector &user_vector) {
    this->push_back(user_vector);

    return *this;
}

template<typename T>
my_stl::vector<T> &my_stl::vector<T>::operator+(vector &&user_vector) {
    this->push_back(std::move(user_vector));

    return *this;
}

template<typename T>
my_stl::vector<T> &my_stl::vector<T>::operator+=(const vector &user_vector) {
    this->push_back(user_vector);

    return *this;
}

template<typename T>
my_stl::vector<T> &my_stl::vector<T>::operator+=(vector &&user_vector) {
    this->push_back(std::move(user_vector));

    return *this;
}

template<typename T>
bool my_stl::vector<T>::operator==(const vector &vector_to_compare) {
    if (number_of_elements != vector_to_compare.number_of_elements) return false;

    for (int i = 0; i < number_of_elements; i++) {
        if (main_buffer[i] != vector_to_compare[i]) return false;
    }

    return true;
}

template<typename T>
size_t my_stl::vector<T>::size() const {
    return number_of_elements;
}
