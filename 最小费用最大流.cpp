const int maxn = ;
const int inf = 0x3f3f3f3f;
// path用来保存找到一条费用最小的增广路
int path[maxn], dis[maxn], head[maxn], vis[maxn], cnt;
void init() {
    cnt = 0;
    memset(head, -1, sizeof(head));
}
struct ac {
    int v, flow, cost, nex;
} edge[maxn];
void addEdge(int u, int v, int flow, int cost) {
    edge[cnt] = {v, flow, cost, head[u]};
    head[u] = cnt++;
    edge[cnt] = {u, 0, -cost, head[v]};
    head[v] = cnt++;
}
int Spfa(int s, int t) {
    memset(dis, inf, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    memset(path, -1, sizeof(path));
    queue<int> que;
    que.push(s);
    dis[s] = 0;
    vis[s] = 1;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        vis[u] = 0;
        for (int i = head[u]; i != -1; i = edge[i].nex) {
            int v = edge[i].v;
            int flow = edge[i].flow;
            int cost = edge[i].cost;
            if (dis[v] > dis[u] + cost && flow > 0) {
                dis[v] = dis[u] + cost;
                path[v] = i;
                if (vis[v])
                    continue;
                vis[v] = 1;
                que.push(v);
            }
        }
    }
    return dis[t] != inf;
}
int MCMF(int s, int t, int& cost) {  //最少费用最大流
    int maxflow = 0;
    while (Spfa(s, t)) {  // Spfa 找最小花费最大流
        int flow = inf;
        //遍历该路上的边，找到最小流量
        // path 存的是这条路的路径，
        // edge[i^1].v 通过反向边得到前驱节点
        for (int i = path[t]; i != -1; i = path[edge[i ^ 1].v]) {
            flow = min(flow, edge[i].flow);
        }
        //找到最小流量后，更新该路上的边的流量
        for (int i = path[t]; i != -1; i = path[edge[i ^ 1].v]) {
            edge[i].flow -= flow;
            edge[i ^ 1].flow += flow;
            cost += flow * edge[i].cost;
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
    return maxflow;  //最大流
}