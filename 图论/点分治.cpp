#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 1e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

struct div_point {
    div_point() {
        int n;
        vector<vector<int>> e(n + 1);
        int totsize, root;
        vector<int> siz(n + 1), maxs(n + 1), mark(n + 1);
        function<void(int, int)> dfs1 = [&](int u, int fa) {
            siz[u] = 1, maxs[u] = 0;
            for (auto v : e[u]) {
                if (v != fa && !mark[v]) {
                    dfs1(v, u);
                    siz[u] += siz[v];
                    maxs[u] = max(maxs[u], siz[v]);
                }
            }
            maxs[u] = max(maxs[u], totsize - siz[u]);
            if (maxs[u] < maxs[root])
                root = u;
        };
        function<void(int)> solve = [&](int rt) {
            mark[rt] = 1;
            /*
        　　　　deal with ans
        　　*/
            int tnt = totsize;
            for (auto v : e[rt]) {
                if (!mark[v]) {
                    totsize = siz[v] > siz[rt] ? tnt - siz[rt] : siz[v];
                    root = 0;
                    dfs1(v, 0);
                    solve(root);
                }
            }
        };
        function<void()> initn = [&]() {
            maxs[0] = n + 1;
            root = 0;
            totsize = n;
            dfs1(1, 0);
            solve(root);
        };
        initn();
    }
};