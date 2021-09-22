#include <bits/stdc++.h>
using namespace std;

/****************************
 * 
 * 
 * 
 ***************************/
struct TwoSat {
    int n, tim, top, scc;
    vector<vector<int>> e;
    vector<int> dfn, low, sta, vis, bel;
    TwoSat(int n_)
        : n(n_) {
        e = vector(2 * n + 1, vector<int>());
        low = vector<int>(2 * n + 1), dfn = low, vis = dfn, sta = vis, bel = sta;
        tim = top = scc = 0;
    }
    void link(int u, int v) {
        e[u].push_back(v);
    }
    void tarjan(int u) {
        dfn[u] = low[u] = ++tim;
        sta[++top] = u;
        vis[u] = 1;
        for (auto v : e[u]) {
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[v], low[u]);
            } else if (vis[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            scc++;
            do {
                u = sta[top--];
                bel[u] = scc;
            } while (dfn[u] != low[u]);
        }
        vis[u] = 0;
    }
    bool twosat(vector<int>& ans) {
        for (int i = 1; i <= 2 * n; i++) {
            if (!dfn[i]) {
                tarjan(i);
            }
        }
        for (int i = 1; i <= n; i++) {
            if (bel[i] == bel[i + n]) {
                return false;
            }
        }
        for (int i = 1; i <= n; i++) {
            ans.push_back(bel[i] < bel[i + n]);
        }
        return true;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    TwoSat ts(n);
    for (int k = 1; k <= m; k++) {
        int i, a, j, b;
        cin >> i >> a >> j >> b;
        ts.link(i + n * a, j + n * (b ^ 1));
        ts.link(j + n * b, i + n * (a ^ 1));
    }
    vector<int> ans;
    if (!ts.twosat(ans)) {
        cout << "IMPOSSIBLE"
             << "\n";
    } else {
        cout << "POSSIBLE"
             << "\n";
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}