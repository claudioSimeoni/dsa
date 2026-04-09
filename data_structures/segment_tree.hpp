#pragma once

#include <cmath>
#include <cstddef>
#include <functional>
#include <vector>

/* the merge function must be ASSOCIATIVE
   the arguments are 0-indexed and the extremes [l, r] */

namespace algo {

struct SegmentTree {
    std::vector<int> tr;
    int n;
    std::function<int(int, int)> merge;
    int neutr;

    SegmentTree(const std::vector<int> &arr, const std::function<int(int, int)> merge, int neutr)
        : merge(merge), neutr(neutr) {
        n = 1 << (int)ceil(log2(arr.size()));
        tr.resize(2 * n, neutr);
        std::copy(arr.begin(), arr.end(), tr.begin() + n);
        for (int i = n - 1; i > 0; i--) tr[i] = merge(tr[2 * i], tr[2 * i + 1]);
    }

    SegmentTree(int dim, const std::function<int(int, int)> merge, int neutr)
        : n(dim), merge(merge), neutr(neutr) {
        n = 1 << (int)ceil(log2(dim));
        tr.resize(2 * n, neutr);
    }

    void upd(int val, int pos) {
        pos = pos + n;
        tr[pos] = val;
        for (pos /= 2; pos > 0; pos /= 2) tr[pos] = merge(tr[2 * pos], tr[2 * pos + 1]);
    }

    int query(int l, int r) {
        int ans = neutr;
        for (l += n, r += n; l <= r; l /= 2, r /= 2) {
            if (l & 1) ans = merge(ans, tr[l++]);
            if (!(r & 1)) ans = merge(ans, tr[r--]);
        }
        return ans;
    }
};

struct RecursiveSegmentTree {
    std::vector<int> tr;
    int n;
    std::function<int(int, int)> merge;
    int neutr;

    RecursiveSegmentTree(const std::vector<int> &arr, const std::function<int(int, int)> merge,
                         int neutr)
        : n(arr.size()), merge(merge), neutr(neutr) {
        tr.resize(4 * n, neutr);
        build(1, 0, n - 1, arr);
    }

    RecursiveSegmentTree(int dim, const std::function<int(int, int)> merge, int neutr)
        : n(dim), merge(merge), neutr(neutr) {
        tr.resize(4 * n, neutr);
    }

    void build(int v, int l, int r, const std::vector<int> &arr) {
        if (l == r) {
            tr[v] = arr[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, arr);
        build(2 * v + 1, m + 1, r, arr);
        tr[v] = merge(tr[2 * v], tr[2 * v + 1]);
    }

    void upd(int v, int l, int r, int val, int pos) {
        if (l == r) {
            tr[v] = val;
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m) upd(2 * v, l, m, val, pos);
        else upd(2 * v + 1, m + 1, r, val, pos);
        tr[v] = merge(tr[2 * v], tr[2 * v + 1]);
    }

    int query(int v, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return neutr;
        if (l >= ql && r <= qr) return tr[v];
        int m = (l + r) / 2;
        return merge(query(2 * v, l, m, ql, qr), query(2 * v + 1, m + 1, r, ql, qr));
    }

    int query(int l, int r) { return query(1, 0, n - 1, l, r); }

    void upd(int val, int pos) { upd(1, 0, n - 1, val, pos); }
};

} // namespace algo