#pragma once

#include <cmath>
#include <functional>
#include <vector>

namespace algo {

/* the merge function must be ASSOCIATIVE and IDEMPOTENT
   the arguments are 0-indexed and the extremes [l, r] */
struct SparseTable {
    std::vector<std::vector<int>> tab;
    std::function<int(int, int)> merge;
    int n;
    int p2;

    SparseTable(std::vector<int> &v, std::function<int(int, int)> merge) : n(v.size()) {
        p2 = (int)std::floor(log2(n)) + 1;
        tab.resize(p2, std::vector<int>(n));

        tab[0] = v;
        for (int i = 1; i < p2; i++) {
            for (int j = 0; j <= n - (1 << i); j++) {
                tab[i][j] = merge(tab[i - 1][j], tab[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int l, int r) {
        int mp2 = (int)std::floor(log2(r - l + 1));
        return merge(tab[mp2][l], tab[mp2][r - (1 << mp2) + 1]);
    }
};

} // namespace algo