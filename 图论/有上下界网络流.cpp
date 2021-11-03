//code sourced from kinesis
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using pii = pair<i64, i64>;
constexpr int N = 6e4 + 10, M = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
struct E {
    int v, next;
    i64 c;
} edge[M];
int p[N], cur[N], eid, d[N], q[N], SS = N - 1, TT = N - 2, S, T;

void link1(int u, int v, i64 c) {
    edge[eid].v = v, edge[eid].c = c, edge[eid].next = p[u], p[u] = eid++;
}
void link2(int u, int v, i64 c) {
    link1(u, v, c), link1(v, u, 0);
}

bool makelevel(int s, int t) {  //广搜标号
    memset(d, 0, sizeof d);
    d[s] = 1;
    int l = 0, r = 0;  //手写队列的指针
    q[r++] = s;
    while (l < r) {
        int u = q[l++];
        if (u == t) {
            return true;  //可达汇点
        }
        for (int i = p[u]; i + 1; i = edge[i].next) {
            int v = edge[i].v;
            if (!d[v] && edge[i].c) {
                q[r++] = v, d[v] = d[u] + 1;
            }
        }
    }
    return false;
}

i64 dfs(int u, i64 flow, int t) {
    if (u == t || !flow) {
        return flow;
    }
    i64 sum = 0;
    for (int& i = cur[u]; i + 1; i = edge[i].next) {
        int v = edge[i].v;
        if (edge[i].c && d[v] == d[u] + 1) {
            i64 tmp = dfs(v, min(1LL * edge[i].c, flow), t);
            edge[i].c -= tmp, edge[i ^ 1].c += tmp;
            flow -= tmp;
            sum += tmp;
            if (!flow) {
                break;
            }
        }
    }

    if (sum == 0) {
        d[u] = -1;  //表示这个点无法放流量了就在此回合屏蔽掉
    }
    return sum;
}
i64 dinic(int s, int t) {
    i64 ans = 0;
    while (makelevel(s, t)) {
        memcpy(cur, p, sizeof cur);
        ans += dfs(s, inf, t);
    }
    return ans;
}

i64 del[N];

int main() {  // ONLINE_JUDGE
    memset(p, -1, sizeof p), eid = 0;
    int n, m;
    cin >> n >> m >> S >> T;
    for (int i = 1; i <= m; i++) {
        int u, v, c1, c2;  //c1<=flow<=c2
        cin >> u >> v >> c1 >> c2;
        del[u] -= c1, del[v] += c1, link2(u, v, c2 - c1);
    }
    for (int i = 1; i <= n; i++) {
        if (del[i] >= 0) {
            link2(SS, i, del[i]);
        } else {
            link2(i, TT, -del[i]);
        }
    }
    dinic(SS, TT);
    link2(T, S, inf);
    int vb = eid - 1;
    dinic(SS, TT);  //保证T->S的反向边是最小流
    for (int i = p[SS]; i + 1; i = edge[i].next) {
        if (edge[i].c) {
            cout << "please go home to sleep\n";
            return 0;  //无解
        }
    }
    int ans = edge[vb].c;  //最小流
    p[S] = edge[p[S]].next, p[T] = edge[p[T]].next;
    ans += dinic(S, T);  //最大流
    cout << ans << "\n";
    return 0;
}

/*
对于原图的边<u,v,L,R>,顶标tpm[u] -= L,tpm[v] += L,连link(u,v,R-L)
对于tpm>0的，连<SS,i,tpm>，否则<i,TT,-tpm>
先跑dinic(SS,TT)。连<T,S,inf>，再跑SS,TT，此时T->S反向边就是最小流
去除T->S的边（将T和S的链前往回指一个指针）。跑S,T，加上这部分流量就是最大流了。
*/
