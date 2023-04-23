#ifndef MY_STL_PRIORITYQUEUE_H
#define MY_STL_PRIORITYQUEUE_H

#include "vector.hxx"

using my_stl::vector;

//default compare function
template<typename T, typename functionCompare = std::greater<T>>
class priorityQueue {
private:
    vector<T> heap;
    functionCompare compare;

    void swap(T &a, T &b);

    void heapifyDown(int index);

    void heapifyUp(int index);

    int parent(int index);

    int leftChild(int index);

    int rightChild(int index);

public:
    explicit priorityQueue(functionCompare compare) : compare(compare) {}

    priorityQueue() = default;

    void push(const T &value);

    void pop();

    const T &top();

    [[nodiscard]] bool empty() const;

    [[nodiscard]] int size() const;

};


#endif //MY_STL_PRIORITYQUEUE_H
