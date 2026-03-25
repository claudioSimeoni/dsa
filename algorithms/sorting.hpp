#pragma once

#include <cstddef>
#include <utility>
#include <vector>

namespace algo {

int inf = 1e9;

struct Sorting {
    static void bubble_sort(std::vector<int> &v) {
        const size_t n = v.size();
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n - 1 - i; j++) {
                if (v[j] > v[j + 1]) std::swap(v[j], v[j + 1]);
            }
        }
    }

    static void selection_sort(std::vector<int> &v) {
        const size_t n = v.size();
        for (size_t i = 0; i < n; i++) {
            int ind = i;
            for (size_t j = i; j < n; j++) {
                if (v[j] < v[ind]) ind = j;
            }
            std::swap(v[i], v[ind]);
        }
    }
};

} // namespace algo
