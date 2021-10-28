#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct E {
    int u, v;
};
/*
* 对 n,m 同阶的图复杂度优秀
* 对于无向图，按<u,v>的度数比较（度数一样按编号比较）来定边，得到 DAG。
* 按度数分层，同层再按编号排序，显然是 DAG
* 由于是 DAG，不存在环。那么对于每个原本的三元环，变成其中一个点 u 指向另两个点 v,w（可能v->w，可能w->v）
* 那么遍历每个 u，给所有的 v 赋值vis[v] = u；遍历每个 v ，如果指向 w 的 vis[w] = u，三元环+1
* 由于枚举的是 u ，所以能遍历到所有的三元环且唯一
* 复杂度分根号的大点小点考虑：首先图遍历的复杂度O(n+m)；大点不超过根号个，所以为根号*O(n)；小点指向小点，所以为O(n)*根号
* 复杂度 O(nsqrt(n)) 
*/
struct TripleRing {
    int n, m;
    ll ans;
    vector<vector<int>> e;
    vector<int> deg, vis;
    vector<E> edges;
    TripleRing(int n_)
        : n(n_) {
        deg = vector<int>(n + 1), vis = deg;
        e = vector<vector<int>>(n + 1);
        ans = 0;
    }
    TripleRing(int n_, vector<E> edges_)  //e_是无向边集合。处理有向图一样，定边后对于每个三元环判一下边
        : TripleRing(n_) {
        edges = edges_;
        m = edges.size();
        for (auto [u, v] : edges) {
            ++deg[u], ++deg[v];
        }
        for (auto [u, v] : edges) {
            if (deg[u] < deg[v] || (deg[u] == deg[v] && u > v)) {  //
                swap(u, v);
            }
            e[u].push_back(v);
        }
        for (int x = 1; x <= n; ++x) {
            for (auto y : e[x]) {
                vis[y] = x;
            }
            for (auto y : e[x]) {
                for (auto z : e[y]) {
                    if (vis[z] == x) {
                        ++ans;
                    }
                }
            }
        }
    }
    ll val() {
        return ans;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<E> edges;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }
    TripleRing tr(n, edges);
    printf("%lld\n", tr.val());
}