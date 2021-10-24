#include <bits/stdc++.h>
using namespace std;
constexpr int M = 1e6 + 5, N = 1e3 + 5, inf = 0x3f3f3f3f;
struct E {
    int v, c, next;
} edge[M];
int p[N], cur[N], eid, d[N], q[N], S, T, SS, TT;

void link1(int u, int v, int c) {
    edge[eid].v = v, edge[eid].c = c, edge[eid].next = p[u], p[u] = eid++;
}
void link2(int u, int v, int c) {
    link1(u, v, c), link1(v, u, 0);
}

bool makelevel(int s, int t)  //广搜标号
{
    memset(d, 0, sizeof d);
    d[s] = 1;
    int l = 0, r = 0;  //手写队列的指针
    q[r++] = s;
    while (l < r) {
        int u = q[l++];
        if (u == t)
            return true;  //可达汇点
        for (int i = p[u]; i + 1; i = edge[i].next) {
            int v = edge[i].v;
            if (!d[v] && edge[i].c)
                q[r++] = v, d[v] = d[u] + 1;
        }
    }
    return false;
}

int dfs(int u, int flow, int t) {
    if (u == t || !flow)
        return flow;
    int sum = 0;
    for (int& i = cur[u]; i + 1; i = edge[i].next) {  //弧优化，表示每次删掉邻接表靠后加入的边（表示这些边已经跑满了，不需要再访问）
        int v = edge[i].v;
        if (edge[i].c && d[v] == d[u] + 1) {
            int tmp = dfs(v, min(edge[i].c, flow), t);
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

int dinic(int s, int t) {
    int ans = 0;
    while (makelevel(s, t)) {
        memcpy(cur, p, sizeof cur);
        ans += dfs(s, inf, t);
    }
    return ans;
}

/*
对于原图的边<u,v,L,R>,顶标tpm[u] -= L,tpm[v] += L,连link(u,v,R-L)
对于tpm>0的，连<SS,i,tpm>，否则<i,TT,-tpm>
先跑dinic(SS,TT)。连<T,S,inf>，再跑SS,TT，此时T->S反向边就是最小流
去除T->S的边（将T和S的链前往回指一个指针）。跑S,T，加上这部分流量就是最大流了。
*/
