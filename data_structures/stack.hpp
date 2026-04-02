#pragma once

#include <cassert>
#include <vector>

namespace algo {

constexpr int max_dim = 1e5;

struct Stack {
    std::vector<int> arr;
    int dim;
    int back;

    Stack() {
        dim = max_dim;
        arr.resize(dim);
        back = 0;
    }

    void push(int k) {
        assert(back < dim);
        arr[back] = k;
        back++;
    }

    int pop() {
        assert(back > 0);
        back--;
        return arr[back];
    }

    int top() {
        assert(back > 0);
        return arr[back - 1];
    }

    bool empty() { return back == 0; }

    int size() { return back; }
};

} // namespace algo