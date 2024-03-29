#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e3 + 5, M = 1e5 + 5;
constexpr int INF = 0x3f3f3f3f;
int n, m, tot = 1, lnk[N], cur[N], ter[M], nxt[M], cap[M], cost[M], dis[N], ret;
bool vis[N];

void add(int u, int v, int w, int c) {
    ter[++tot] = v, nxt[tot] = lnk[u], lnk[u] = tot, cap[tot] = w, cost[tot] = c;
}
void addedge(int u, int v, int w, int c) {
    add(u, v, w, c), add(v, u, 0, -c);
}
bool spfa(int s, int t) {
    memset(dis, 0x3f, sizeof(dis));
    memcpy(cur, lnk, sizeof(lnk));
    std::queue<int> q;
    q.push(s), dis[s] = 0, vis[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop(), vis[u] = 0;
        for (int i = lnk[u]; i; i = nxt[i]) {
            int v = ter[i];
            if (cap[i] && dis[v] > dis[u] + cost[i]) {
                dis[v] = dis[u] + cost[i];
                if (!vis[v])
                    q.push(v), vis[v] = 1;
            }
        }
    }
    return dis[t] != INF;
}
int dfs(int u, int t, int flow) {
    if (u == t)
        return flow;
    vis[u] = 1;
    int ans = 0;
    for (int& i = cur[u]; i && ans < flow; i = nxt[i]) {
        int v = ter[i];
        if (!vis[v] && cap[i] && dis[v] == dis[u] + cost[i]) {
            int x = dfs(v, t, std::min(cap[i], flow - ans));
            if (x)
                ret += x * cost[i], cap[i] -= x, cap[i ^ 1] += x, ans += x;
        }
    }
    vis[u] = 0;
    return ans;
}
int mcmf(int s, int t) {
    int ans = 0;
    while (spfa(s, t)) {
        int x;
        while ((x = dfs(s, t, INF)))
            ans += x;
    }
    return ans;
}
int main() {
    int s, t;
    cin >> n >> m >> s >> t;
    while (m--) {
        int u, v, w, c;
        cin >> u >> v >> w >> c;
        addedge(u, v, w, c);
    }
    int ans = mcmf(s, t);
    cout << ans << " " << ret << "\n";  //ret为费用
    //ret = 0;//ret是全局，需要清空
    return 0;
}