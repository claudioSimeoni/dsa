#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace algo {

template <class T> struct Heap {
    std::vector<T> tr;
    int n;

    Heap() {
        n = 0;
        tr.resize(n + 1);
    }

    void insert(T k) {
        n++;
        if (tr.size() - 1 < n) tr.push_back(k);
        tr[n] = k;

        for (int i = n; i > 1; i /= 2) {
            if (tr[i / 2] > tr[i]) std::swap(tr[i / 2], tr[i]);
        }
    }

    T pop() {
        assert(n > 0);
        std::swap(tr[1], tr[n]);
        n--;
        heapify(1);
        return tr[n + 1];
    }

    T top() {
        assert(n > 0);
        return tr[1];
    }

    void heapify(int nd) {
        int l = 2 * nd, r = 2 * nd + 1;
        int head = nd;

        if (l <= n && tr[l] < tr[head]) head = l;
        if (r <= n && tr[r] < tr[head]) head = r;

        if (head != nd) {
            std::swap(tr[head], tr[nd]);
            heapify(head);
        }
    }
};

} // namespace algo