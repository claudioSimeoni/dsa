#pragma once

#include <cassert>
#include <vector>

namespace algo {

constexpr int max_dim = 1e5;

struct Queue {
    std::vector<int> arr;
    int dim;
    int sz;
    int front;
    int back;

    Queue() {
        dim = max_dim;
        arr.resize(dim);
        front = 0;
        back = 0;
    }

    void push_back(int k) {
        assert(sz < dim);
        arr[back] = k;
        back = (back + 1) % dim;
        sz++;
    }

    int pop_front() {
        assert(sz > 0);
        int data = arr[front];
        front = (front + 1) % dim;
        sz--;
        return data;
    }

    int head() {
        assert(sz > 0);
        return arr[front];
    }

    int tail() {
        assert(sz > 0);
        return arr[(back - 1) % dim];
    }

    bool empty() { return sz == 0; }

    int size() { return sz; }
};

} // namespace algo