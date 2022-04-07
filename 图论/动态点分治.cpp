#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int siz[N], maxs[N], totsize, root, dis[N][30], f[N][30], dep[N];
bool mark[N];
vector<vector<int>> e(N);

void dfs1(int u, int fa) {
    siz[u] = 1, maxs[u] = 0;
    for (auto v : e[u]) {
        // int v = edge[i].v;
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

void dfsinit(int u, int fa, int k, int d) {
    dep[u]++;  // the level of the heavy point
    dis[u][dep[u]] = d;
    f[u][dep[u]] = k;
    for (auto v : e[u]) {
        // int v = edge[i].v;
        if (mark[v])
            continue;
        dfsinit(v, u, k, d + 1);
    }
}

void solve(int rt) {
    mark[rt] = 1;
    dfsinit(rt, 0, rt, 0);
    int tnt = totsize;
    for (auto v : e[rt]) {
        // int v = edge[i].v;
        if (mark[v])
            continue;
        totsize = siz[v] > siz[rt] ? tnt - siz[rt] : siz[v];
        root = 0;
        dfs1(v, rt);
        solve(root);
    }
}
