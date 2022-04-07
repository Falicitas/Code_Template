# Dijkstra费用流

```cpp

#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

//求最小费用最大流。若求最大费用则边权取反跑最短路。由于spfa求完势能后边权非负，所以dijk跑最短路是ok的
//复杂度不超过O(|f|(n+m)log) + O(n * m),其中 |f| 是最大流，O(n*m) 是 spfa 求势能函数
struct cost_flow {
    struct edge {
        int v, next;
        i64 f, w;
        edge(int v, i64 f, i64 w, int next)
            : v(v), f(f), w(w), next(next) {}
    };
    vector<edge> e;
    struct node {
        int v, e;  //前导点v，前导边e
    };
    vector<node> p;
    struct mypair {
        i64 dis;
        int id;
        mypair(i64 d, int x)
            : dis(d), id(x) {
        }
        bool operator<(const mypair& a) const {
            return dis > a.dis;
        }
    };
    vector<int> head, vis, cur, now;  // cur用作弧优化
    vector<i64> dis, h;
    int n, s, t;
    cost_flow(int n_, int s, int t)  //构造函数初始化
        : n(n_), s(s), t(t) {
        n = n + 5;
        p.resize(n), head.resize(n, -1), cur.resize(n), vis.resize(n), h.resize(n), now.resize(n), dis.resize(n);
    }
    void addedge(int u, int v, i64 f, i64 w) {
        // cout << u << "," << v << ":flow:" << f << ",cost:" << w << "\n";
        e.emplace_back(v, f, w, head[u]);
        head[u] = (int)e.size() - 1;
        e.emplace_back(u, 0, -w, head[v]);
        head[v] = (int)e.size() - 1;
    }
    bool dijkstra() {
        priority_queue<mypair> q;
        fill(dis.begin(), dis.end(), INF);
        fill(vis.begin(), vis.end(), 0);
        dis[s] = 0;
        q.push(mypair(0, s));
        while (!q.empty()) {
            int u = q.top().id;
            q.pop();
            if (vis[u])
                continue;
            vis[u] = 1;
            for (int i = head[u]; i + 1; i = e[i].next) {
                int v = e[i].v;
                i64 nc = e[i].w + h[u] - h[v];
                if (e[i].f && dis[v] > dis[u] + nc) {
                    dis[v] = dis[u] + nc;
                    p[v].v = u;
                    p[v].e = i;
                    q.push(mypair(dis[v], v));
                }
            }
        }
        return dis[t] != INF;
    }
    void spfa() {
        queue<int> q;
        fill(h.begin(), h.end(), INF);
        h[s] = 0, vis[s] = 1;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (int i = head[u]; i + 1; i = e[i].next) {
                int v = e[i].v;
                if (e[i].f && h[v] > h[u] + e[i].w) {  //对势能函数求最短路（由于含负权边，使用SPFA）
                    h[v] = h[u] + e[i].w;
                    if (!vis[v]) {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
    }
    int DFS(int u, i64 c, int t) {
        if (u == t) {
            return c;
        }
        i64 r = c;   // r表示剩余可用的流量
        now[u] = 1;  // v标志u在弧上
        for (int& i = cur[u]; i + 1 && r; i = e[i].next) {
            int v = e[i].v;
            i64 f = e[i].f;
            i64 w = e[i].w + h[u] - h[v];
            if (!now[v] && f && dis[u] + w == dis[v]) {
                int x = DFS(v, min(r, f), t);
                r -= x;
                e[i].f -= x;
                e[i ^ 1].f += x;
            }
        }
        now[u] = 0;
        return c - r;  // c-r表示使用掉的最大流量
    }
    void run(int& mf, i64& mw) {
        mf = 0, mw = 0;
        spfa();
        while (dijkstra()) {
            cur = head;
            i64 c = DFS(s, INF, t);
            for (int i = 0; i < n; ++i)
                if (dis[i] < INF)
                    h[i] += dis[i];
            mf += c;
            mw += c * h[t];
        }
    }
};

```