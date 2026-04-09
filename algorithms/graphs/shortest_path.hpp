#pragma once

#include <queue>
#include <vector>

namespace algo {

struct ShortestPath {

    static void dijkstra(int s, std::vector<std::vector<std::pair<int, int>>> &adj, std::vector<int> &dis) {
        int n = adj.size();
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        dis[s] = 0;
        pq.push({0, s});

        while (!pq.empty()) {
            auto [d, nd] = pq.top();
            pq.pop();

            if (d > dis[nd]) continue;

            for (auto [edge, ad] : adj[nd]) {
                if (dis[nd] + edge < dis[ad]) {
                    dis[ad] = dis[nd] + edge;
                    pq.push({dis[ad], ad});
                }
            }
        }
    };
};

} // namespace algo