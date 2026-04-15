#pragma once

#include <cmath>
#include <cstddef>
#include <functional>
#include <vector>
#include <algorithm>

/* the merge function must be ASSOCIATIVE
   the arguments are 0-indexed and the extremes [l, r) */
namespace algo {

template <class T, class F> struct SegmentTree {
    std::vector<T> tr;
    int n;

    SegmentTree(const std::vector<T> &arr) {
        n = 1 << (int)ceil(log2(arr.size()));
        tr.resize(2 * n, F().neutral);
        std::copy(arr.begin(), arr.end(), tr.begin() + n);
        for (int i = n - 1; i > 0; i--) tr[i] = F()(tr[2 * i], tr[2 * i + 1]);
    }

    void upd(T val, int pos) {
        pos = pos + n;
        tr[pos] = val;
        for (pos /= 2; pos > 0; pos /= 2) tr[pos] = F()(tr[2 * pos], tr[2 * pos + 1]);
    }

    T query(int l, int r) {
        T ans = F().neutral;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) ans = F()(ans, tr[l++]);
            if (r & 1) ans = F()(ans, tr[--r]);
        }
        return ans;
    }
};


template <class T, class F>
struct LazySegmentTree {
    struct Node {
        T val, add, set;
        bool to_set;
    };

    std::vector<Node> tr;
    int n;

    LazySegmentTree(std::vector<T> &arr) {
        n = arr.size();
        tr.resize(4 * n, {F().neutral, 0, 0, 0});
        build(1, 0, n, arr);
    }

    void build(int v, int l, int r, std::vector<T> &arr) {
        if (r - l <= 1) {
            tr[v].val = arr[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, arr);
        build(2 * v + 1, m, r, arr);
        tr[v].val = F()(tr[2 * v].val, tr[2 * v + 1].val);
    }

    void push(int v, int l, int r) {
        int m = (l + r) / 2;
        if (tr[v].to_set) {
            apply_set(2 * v, m - l, tr[v].set);
            apply_set(2 * v + 1, r - m, tr[v].set);
            tr[v].to_set = false;
        }
        if (tr[v].add) {
            apply_add(2 * v, m - l, tr[v].add);
            apply_add(2 * v + 1, r - m, tr[v].add);
            tr[v].add = 0;
        }
    }

    void apply_add(int v, int len, T to_add) {
        if (tr[v].to_set) tr[v].set += to_add;
        else tr[v].add += to_add;
        tr[v].val += len * to_add;
    }

    void apply_set(int v, int len, T to_set) {
        tr[v].val = len * to_set;
        tr[v].set = to_set;
        tr[v].to_set = true;
        tr[v].add = 0;
    }

    T query(int v, int l, int r, int ql, int qr) {
        push(v, l, r);
        if (l >= qr || r <= ql) return F().neutral;
        if (r <= qr && l >= ql) return tr[v].val;
        return F()(query(2 * v, l, (l + r) / 2, ql, qr), query(2 * v + 1, (l + r) / 2, r, ql, qr));
    }

    void add(int v, int l, int r, int ql, int qr, T to_add) {
        push(v, l, r);
        if (l >= qr || r <= ql) return;
        if (r <= qr && l >= ql) {
            apply_add(v, r - l, to_add);
            return;
        }
        add(2 * v, l, (l + r) / 2, ql, qr, to_add);
        add(2 * v + 1, (l + r) / 2, r, ql, qr, to_add);
        tr[v].val = F()(tr[2 * v].val, tr[2 * v + 1].val);
    }

    void set(int v, int l, int r, int ql, int qr, T to_set) {
        push(v, l, r);
        if (l >= qr || r <= ql) return;
        if (r <= qr && l >= ql) {
            apply_set(v, r - l, to_set);
            return;
        }
        set(2 * v, l, (l + r) / 2, ql, qr, to_set);
        set(2 * v + 1, (l + r) / 2, r, ql, qr, to_set);
        tr[v].val = F()(tr[2 * v].val, tr[2 * v + 1].val);
    }

    T query(int l, int r) { return query(1, 0, n, l, r); }

    void add(int l, int r, T val) { add(1, 0, n, l, r, val); }

    void set(int l, int r, T val) { set(1, 0, n, l, r, val); }
};


template <class T, class F> struct RecursiveSegmentTree {
    std::vector<T> tr;
    int n;

    RecursiveSegmentTree(const std::vector<T> &arr) : n(arr.size()) {
        tr.resize(4 * n, F().neutral);
        build(1, 0, n, arr);
    }

    void build(int v, int l, int r, const std::vector<T> &arr) {
        if (r - l == 1) {
            tr[v] = arr[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, arr);
        build(2 * v + 1, m, r, arr);
        tr[v] = F()(tr[2 * v], tr[2 * v + 1]);
    }

    void upd(int v, int l, int r, T val, int pos) {
        if (r - l == 1) {
            tr[v] = val;
            return;
        }
        int m = (l + r) / 2;
        if (pos < m) upd(2 * v, l, m, val, pos);
        else upd(2 * v + 1, m, r, val, pos);
        tr[v] = F()(tr[2 * v], tr[2 * v + 1]);
    }

    T query(int v, int l, int r, int ql, int qr) {
        if (l >= qr || r <= ql) return F().neutral;
        if (l >= ql && r <= qr) return tr[v];
        int m = (l + r) / 2;
        return F()(query(2 * v, l, m, ql, qr), query(2 * v + 1, m, r, ql, qr));
    }

    int query(int l, int r) { return query(1, 0, n, l, r); }

    void upd(T val, int pos) { upd(1, 0, n, val, pos); }
};

} // namespace algo