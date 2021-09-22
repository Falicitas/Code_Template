#include <bits/stdc++.h>
using namespace std;

//当场自敲一发更好。根据题目来敲

typedef long long i64;

struct dijkstra {
    vector<i64> d;
    vector<int> vis;
    vector<vector<pair<int, i64>>> e;
    const int inf = 0x3f3f3f3f3f3f3f3f;
    dijkstra(vector<vector<pair<int, i64>>> e_)
        : e(e_) {
    }
    void dijk(int S)  //non_negative value graph
    {
        d = vector<i64>(e.size(), inf);
        vis = vector<int>(e.size());
        d[S] = 0;
        auto cmp = [&](pair<int, i64> x, pair<int, i64> y) {
            return x.second > y.second;
        };
        priority_queue<pair<i64, int>, vector<pair<i64, int>>, decltype(cmp)> pq(cmp);
        pq.emplace(S, 0);
        while (!pq.empty()) {
            auto [u, dis] = pq.top();
            pq.pop();
            if (vis[u]) {
                continue;
            }
            vis[u] = 1;
            for (auto [v, w] : e[u]) {
                if (!vis[v] && d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    pq.emplace(v, d[v]);
                }
            }
        }
    }
};