#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
//加了弧优化

constexpr int M = 1e6 + 5, N = 1e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
struct E {
    int v, c, next;
} edge[M];
int p[N], cur[N], eid, d[N], s, t, now[N];

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

i64 dfs(int u, i64 flow) {
    if (u == t || !flow)
        return flow;
    i64 sum = 0;
    now[u] = 1;
    for (int& i = cur[u]; i + 1; i = edge[i].next) {  //弧优化，表示每次删掉邻接表靠后加入的边（表示这些边已经跑满了，不需要再访问）
        int v = edge[i].v;
        if (!now[v] && edge[i].c && d[v] == d[u] + 1) {
            i64 tmp = dfs(v, min(1ll * edge[i].c, flow));
            edge[i].c -= tmp, edge[i ^ 1].c += tmp;
            flow -= tmp;
            sum += tmp;
            if (!flow)
                break;
        }
    }
    now[u] = 0;
    if (sum == 0)
        d[u] = -1;  //表示这个点无法放流量了就在此回合屏蔽掉
    return sum;
}

i64 dinic() {
    i64 ans = 0;
    while (makelevel()) {
        memcpy(cur, p, sizeof cur);
        ans += dfs(s, inf);
    }
    return ans;
}

int main() {
    init();
    int n, m;
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        link2(u, v, w);
    }
    cout << dinic() << "\n";
}