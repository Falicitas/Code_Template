//加了弧优化
struct E {
    int v, c, next;
} edge[M];
int p[N], cur[N], eid, d[N], q[N], s, t;

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
    int l = 0, r = 0;  //手写队列的指针
    q[r++] = s;
    while (l < r) {
        int u = q[l++];
        if (u == t)
            return true;  //可达汇点
        UREP(i, u) {
            int v = edge[i].v;
            if (!d[v] && edge[i].c)
                q[r++] = v, d[v] = d[u] + 1;
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
