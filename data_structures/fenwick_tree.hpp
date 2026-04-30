#pragma once

#include <vector>

namespace algo {

template <class T> struct Fenwick {
    std::vector<T> tr;
    int n;

    Fenwick(std::vector<T> &v) : n(v.size()) {
        tr.resize(n + 1);
        for (int i = 0; i < n; i++) add(i, v[i]);
    }

    void add(int pos, T val) {
        for (pos++; pos <= n; pos += pos & -pos) tr[pos] += val;
    }

    void set(int pos, T val) { add(pos, val - (pref(pos) - pref(pos - 1))); }

    int pref(int pos) {
        T ans = 0;
        for (pos++; pos > 0; pos -= pos & -pos) ans += tr[pos];
        return ans;
    }

    // [l, r)
    int query(int l, int r) { return pref(r - 1) - pref(l - 1); }
};


/* point query range update (much shorter than the lazy segment if you don't need range queries)
   is obtained by using the difference array */
template <class T> struct FenwickPQRU {
    std::vector<T> tr;
    int n;

    FenwickPQRU(std::vector<T> &v) : n(v.size()) {
        tr.resize(n + 1);
        for (int i = 0; i < n; i++) add(i, i + 1, v[i]);
    }

    void add(int pos, T val) {
        for (pos++; pos <= n; pos += pos & -pos) tr[pos] += val;
    }

    int query(int pos) {
        T ans = 0;
        for (pos++; pos > 0; pos -= pos & -pos) ans += tr[pos];
        return ans;
    }

    void add(int l, int r, int val) {
        add(l, val);
        add(r, -val);
    }
};

} // namespace algo