# Dinic

```cpp

#include <bits/stdc++.h>
using namespace std;
//加了弧优化

constexpr int M = 1e6 + 5, N = 1e5 + 5, inf = 0x3f3f3f3f;
struct E {
    int v, c, next;
} edge[M];
int p[N], cur[N], eid, d[N], s, t;

void init() {
    memset(p, -1, sizeof p);
    eid = 0;
}

void link1(int u, int v, int c) {
    edge[eid].v = v, edge[eid].c = c, edge[eid].next = p[u], p[u] = eid++;
}
void link2(int u, int v, int c) {
    link1(u, v, c), link1(v, u, 0);
}

bool makelevel()  //广搜标号
{
    memset(d, 0, sizeof d);
    d[s] = 1;
    queue<int> q;
    q.emplace(s);
    while (q.size()) {
        int u = q.front();
        q.pop();
        if (u == t)
            return true;  //可达汇点
        for (int i = p[u]; i + 1; i = edge[i].next) {
            int v = edge[i].v;
            if (!d[v] && edge[i].c)
                q.emplace(v), d[v] = d[u] + 1;
        }
    }
    return false;
}

int dfs(int u, int flow) {
    if (u == t || !flow)
        return flow;
    int sum = 0;
    for (int& i = cur[u]; i + 1; i = edge[i].next) {  //弧优化，表示每次删掉邻接表靠后加入的边（表示这些边已经跑满了，不需要再访问）
        int v = edge[i].v;
        if (edge[i].c && d[v] == d[u] + 1) {
            int tmp = dfs(v, min(edge[i].c, flow));
            edge[i].c -= tmp, edge[i ^ 1].c += tmp;
            flow -= tmp;
            sum += tmp;
            if (!flow)
                break;
        }
    }
    if (sum == 0)
        d[u] = -1;  //表示这个点无法放流量了就在此回合屏蔽掉
    return sum;
}

int dinic() {
    int ans = 0;
    while (makelevel()) {
        memcpy(cur, p, sizeof cur);
        ans += dfs(s, inf);
    }
    return ans;
}


```