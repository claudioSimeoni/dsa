#pragma once

#include <cstddef>
#include <utility>
#include <vector>

namespace algo {

constexpr int inf = 1e9;

struct Sorting {
    static void bubble_sort(std::vector<int> &v) {
        const int n = v.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 1 - i; j++) {
                if (v[j] > v[j + 1]) std::swap(v[j], v[j + 1]);
            }
        }
    }

    static void selection_sort(std::vector<int> &v) {
        const int n = v.size();
        for (int i = 0; i < n; i++) {
            int ind = i;

            for (int j = i; j < n; j++) {
                if (v[j] < v[ind]) ind = j;
            }
            std::swap(v[i], v[ind]);
        }
    }

    static void insertion_sort(std::vector<int> &v) {
        const int n = v.size();
        for (int i = 1; i < n; i++) {
            int key = v[i];
            int j;

            for (j = i - 1; j >= 0 && v[j] > key; j++) {
                v[j + 1] = v[j];
            }
            v[j + 1] = key;
        }
    }

    // [l, r)
    static void merge_sort(std::vector<int> &v, const int l, const int r) {
        const int n = r - l;
        const int m = (l + r) / 2;
        if (n <= 1) return;
        merge_sort(v, l, m);
        merge_sort(v, m, r);

        int lptr = l, rptr = m;
        std::vector<int> temp(n);
        for (int i = 0; i < n; i++) {
            if (lptr >= m) temp[i] = v[rptr++];
            else if (rptr >= r) temp[i] = v[lptr++];
            else {
                if (v[rptr] < v[lptr]) temp[i] = v[rptr++];
                else temp[i] = v[lptr++];
            }
        }

        std::copy(temp.begin(), temp.end(), v.begin() + l);
    }

    static void counting_sort(std::vector<int> &v, int max_val) {
        const int n = v.size();
        std::vector<int> occ(max_val + 1);
        for (int &x : v) occ[x]++;

        int optr = 0;
        for (int i = 0; i < n; i++) {
            while (!occ[optr]) {
                optr++;
                continue;
            }
            occ[optr]--;
            v[i] = optr;
        }
    }
};

} // namespace algo