#pragma once

#include <algorithm>
#include <cmath>
#include <vector>

namespace algo {

struct Ancestors {
    std::vector<int> depth;
    std::vector<std::vector<int>> table;
    int n;
    int lg2;

    Ancestors(std::vector<std::vector<int>> &adj) {
        n = adj.size();
        lg2 = (int)log2(n) + 1;
        depth.resize(n);
        table.resize(lg2, std::vector<int>(n, -1));

        // computing depths
        dfs(0, -1, adj);

        // computing ancestors table
        for (int i = 1; i < lg2; i++) {
            for (int j = 0; j < n; j++) {
                int half = table[i - 1][j];
                if (half == -1) continue;
                table[i][j] = table[i - 1][half];
            }
        }
    }

    void dfs(int nd, int pr, const std::vector<std::vector<int>> &adj) {
        if (pr != -1) depth[nd] = depth[pr] + 1;
        table[0][nd] = pr;
        for (int ad : adj[nd]) {
            if (ad != pr) dfs(ad, nd, adj);
        }
    }

    int kth_ancestor(int nd, int k) const {
        for (int i = 0; i < lg2; i++) {
            if (!(k & (1 << i))) continue;
            nd = table[i][nd];
            if (nd == -1) break;
        }

        return nd;
    }

    int lca(int a, int b) const {
        if (depth[a] < depth[b]) std::swap(a, b);
        a = kth_ancestor(a, depth[a] - depth[b]);
        if (a == b) return a;

        for (int i = lg2 - 1; i >= 0; i--) {
            if (table[i][a] != table[i][b]) {
                a = table[i][a];
                b = table[i][b];
            }
        }

        return table[0][a];
    }
};

} // namespace algo