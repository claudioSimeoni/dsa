#pragma once

#include <queue>
#include <vector>
#include <algorithm>

namespace algo {

constexpr int INF = 1e9;

struct ShortestPath {

    static void dijkstra(int s, const std::vector<std::vector<std::pair<int, int>>> &adj, std::vector<int> &dis) {
        int n = adj.size();
        fill(dis.begin(), dis.end(), INF);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        dis[s] = 0;
        pq.push({0, s});

        while (!pq.empty()) {
            auto [d, nd] = pq.top();
            pq.pop();

            if (d > dis[nd]) continue;

            for (auto [to, w] : adj[nd]) {
                if (dis[nd] + w < dis[to]) {
                    dis[to] = dis[nd] + w;
                    pq.push({dis[to], to});
                }
            }
        }
    };
};

} // namespace algo