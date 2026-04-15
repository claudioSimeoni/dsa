#pragma once

#include <cassert>
#include <vector>

namespace algo {

constexpr int MAX_DIM = 1e5;

template <class T> struct Queue {
    std::vector<T> arr;
    int dim;
    int curr_size;
    int front;
    int back;

    Queue() {
        dim = MAX_DIM;
        curr_size = 0;
        arr.resize(dim);
        front = 0;
        back = 0;
    }

    void push_back(T k) {
        assert(curr_size < dim);
        arr[back] = k;
        back = (back + 1) % dim;
        curr_size++;
    }

    T pop_front() {
        assert(curr_size > 0);
        T data = arr[front];
        front = (front + 1) % dim;
        curr_size--;
        return data;
    }

    T &head() {
        assert(curr_size > 0);
        return arr[front];
    }

    T &tail() {
        assert(curr_size > 0);
        return arr[(back - 1) % dim];
    }

    bool empty() const { return curr_size == 0; }

    int size() const { return curr_size; }
};

} // namespace algo