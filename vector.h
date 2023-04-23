#pragma once

#include <iostream>

namespace my_stl {
    template<typename T>
    class vector {
    protected:
        size_t current_size{};
        size_t number_of_elements{};

        void expand_twice_the_size();

        T *copy_array(T *pointer_to_array_that_should_be_copied, size_t size_of_array, bool double_size);

        //Check if buffer have enough space to take "x" elements
        [[nodiscard]] bool enough_buffer_space(size_t space_to_add) const;

        void copy_vector(const vector &user_vector);

        void move_vector(vector &&user_vector) noexcept;

    public:
        T *main_buffer = nullptr;

        vector();

        explicit vector(size_t size_of_vector);

        vector(const vector &user_vector);

        vector(vector &&user_vector) noexcept;

        ~vector();

        //Returning references to allow chained calls
        vector &push_back(const T &user_value);

        vector &push_back(const T *user_arr, size_t size_of_user_arr);

        vector &push_back(const vector &user_vector);

        vector &push_back(vector &&user_vector);

        void pop();

        void pop_front();

        void pop_index(size_t index_of_element);

        //Chaining methods below doesn't make much sense
        void shrink_to_fit();

        void clear();

        //Returns the value of i element of main buffer
        T &i_element(size_t index, bool safe_mode = false);

        T &operator[](size_t index);

        const T &i_element(size_t index, bool safe_mode = false) const;

        const T &operator[](size_t index) const;

        vector &operator=(const vector &user_vector);

        vector &operator=(vector &&user_vector) noexcept;

        vector &operator+(const vector &user_vector);

        vector &operator+(vector &&user_vector);

        vector &operator+=(const vector &user_vector);

        vector &operator+=(vector &&user_vector);

        bool operator==(const vector &vector_to_compare);

        [[nodiscard]] size_t size() const;

    };
}
