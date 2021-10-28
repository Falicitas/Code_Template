#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
constexpr int inf = 0x3f3f3f3f;
int siz[maxn], maxs[maxn], totsize, root;
bool mark[maxn];
vector<vector<int>> e;
int n;

void dfs1(int u, int fa) {
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
}

void solve(int rt) {
    mark[rt] = 1;
    /*
　　　　deal with ans
　　*/
    int tnt = totsize;
    for (auto v : e[rt]) {
        if (!mark[v]) {
            totsize = (siz[v] > siz[rt] ? tnt - siz[rt] : siz[v]);
            root = 0;
            dfs1(v, 0);
            solve(root);
        }
    }
}

void intn() {
    maxs[0] = inf;
    root = 0;
    totsize = n;
    dfs1(1, 0);
    solve(root);
}
