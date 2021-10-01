#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

struct cost_flow {
    struct edge {
        int v, f, w, next;
    };
    vector<edge> e;
    struct node {
        int v, e;  //前导点v，前导边e
    };
    vector<node> p;
    struct mypair {
        int dis, id;
        bool operator<(const mypair& a) const { return dis > a.dis; }
        mypair(int d, int x) { dis = d, id = x; }
    };
    vector<int> head, dis, vis, h, cur, now;  //cur用作弧优化
    int n, s, t;
    cost_flow(int n, int s, int t)  //构造函数初始化
        : n(n), s(s), t(t) {
        int N = n + 5;
        p.resize(N), head.resize(N, -1), cur.resize(N), vis.resize(N), h.resize(N), now.resize(N), dis.resize(N);
    }
    void init(int n_, int s_, int t_) {
        int N = n + 5;
        n = n_, s = s_, t = t_;
        p.resize(N), head.resize(N, -1), cur.resize(N), vis.resize(N), h.resize(N), now.resize(N), dis.resize(N);
    }
    void addedge(int u, int v, int f, int w) {
        e.push_back({v, f, w, head[u]});
        head[u] = (int)e.size() - 1;
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
                int v = e[i].v, nc = e[i].w + h[u] - h[v];
                if (e[i].f && dis[v] > dis[u] + nc) {
                    dis[v] = dis[u] + nc;
                    p[v].v = u;
                    p[v].e = i;
                    if (!vis[v]) {
                        q.push(mypair(dis[v], v));
                    }
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

    int DFS(int u, int c, int t) {
        if (u == t) {
            return c;
        }
        int r = c;   //r表示剩余可用的流量
        now[u] = 1;  //v标志u在弧上
        for (int& i = cur[u]; i + 1 && r; i = e[i].next) {
            int v = e[i].v, f = e[i].f, w = e[i].w + h[u] - h[v];
            if (!now[v] && f && dis[u] + w == dis[v]) {
                int x = DFS(v, min(r, f), t);
                r -= x;
                e[i].f -= x;
                e[i ^ 1].f += x;
            }
        }
        now[u] = 0;
        return c - r;  //c-r表示使用掉的最大流量
    }
    void run(int& mf, int& mw) {
        mf = 0, mw = 0;
        spfa();  // 先求出初始势能h(x)
        while (dijkstra()) {
            cur = head;
            int c = DFS(s, INF, t);
            for (int i = 1; i <= n; ++i)
                if (dis[i] < INF)
                    h[i] += dis[i];
            mf += c;
            mw += c * h[t];
        }
    }
};

int main() {
    //freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    cost_flow C(n, s, t);
    for (int i = 1; i <= m; i++) {
        int u, v, f, w;
        cin >> u >> v >> f >> w;
        C.addedge(u, v, f, w);
        C.addedge(v, u, 0, -w);
    }
    int mf, mw;
    C.run(mf, mw);
    std::cout << mf << " " << mw << "\n";
    return 0;
}