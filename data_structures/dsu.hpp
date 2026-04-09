#pragma once

#include <cstddef>
#include <utility>
#include <vector>

namespace algo {

struct DSU {
    std::vector<int> tr;

    DSU(int n) { tr.resize(n, -1); }

    int find(int k) {
        if (tr[k] < 0) return k;
        else return tr[k] = find(tr[k]);
    }

    bool merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (tr[a] > tr[b]) std::swap(a, b);
        tr[a] += tr[b];
        tr[b] = a;
        return true;
    }

    bool connected(int a, int b) { return find(a) == find(b); }
};

} // namespace algo