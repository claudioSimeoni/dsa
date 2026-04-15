#pragma once

#include <cmath>
#include <functional>
#include <vector>

namespace algo {

/* the merge function must be ASSOCIATIVE and IDEMPOTENT
   the arguments are 0-indexed and the extremes [l, r) */
template <class T, class F> struct SparseTable {
    std::vector<std::vector<T>> tab;
    int n;
    int lg2;

    SparseTable(std::vector<T> &v) : n(v.size()){
        lg2 = (int)log2(n) + 1;
        tab.resize(lg2, std::vector<T>(n));

        tab[0] = v;
        for (int i = 1; i < lg2; i++) {
            for (int j = 0; j <= n - (1 << i); j++) {
                tab[i][j] = F()(tab[i - 1][j], tab[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    T query(int l, int r) {
        int mp2 = (int)log2(r - l);
        return F()(tab[mp2][l], tab[mp2][r - (1 << mp2)]);
    }
};

} // namespace algo