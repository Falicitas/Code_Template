#include <bits/stdc++.h>
using namespace std;
constexpr int inf = 0x3f3f3f3f;
struct Prim {
    typedef long long ll;
    int n;  //用于找最小距离来扩展
    vector<int> mark, dist, to;
    vector<vector<pair<int, int>>> e;  //二元组为{v,距离w}
    Prim(int n, vector<vector<pair<int, int>>> e)
        : n(n), e(e) {
        mark.resize(n + 1), dist.resize(n + 1), to.resize(n + 1);
    }
    int prim() {
        ll ans = 0;
        int rt = 1, cc = n;
        for (int i = 0; i <= n; i++)
            dist[i] = inf;
        dist[rt] = 0;
        while (cc) {
            int cur = 0;
            for (int i = 1; i <= n; i++)
                if (!mark[i] && dist[i] < dist[cur])
                    cur = i;
            //if (cc < n) link(cur, to[cur]);  //MST 连边
            ans += dist[cur];
            cc--, mark[cur] = 1;
            for (auto vw : e[cur]) {
                auto v = vw.first, w = vw.second;
                if (!mark[v] && dist[v] > w) {
                    dist[v] = w;
                    to[v] = cur;
                }
            }
        }
        return ans;
    }
};
