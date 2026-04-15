#pragma once

#include <cassert>
#include <vector>

namespace algo {

constexpr int MAX_DIM = 1e5;

template <class T> struct Stack {
    std::vector<T> arr;
    int dim;
    int back;

    Stack() {
        dim = MAX_DIM;
        arr.resize(dim);
        back = 0;
    }

    void push(T k) {
        assert(back < dim);
        arr[back] = k;
        back++;
    }

    T pop() {
        assert(back > 0);
        back--;
        return arr[back];
    }

    T &top() {
        assert(back > 0);
        return arr[back - 1];
    }

    bool empty() const { return back == 0; }

    int size() const { return back; }
};

} // namespace algo