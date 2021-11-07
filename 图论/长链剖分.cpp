#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 1e6 + 5;
int n, to[N << 1], nxt[N << 1], head[N], cnt;
int len[N], son[N], tmp[N], *f[N], *id = tmp, ans[N];
void link(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    to[++cnt] = u;
    nxt[cnt] = head[v];
    head[v] = cnt;
}
void dfs(int u, int ff) {
    for (int e = head[u]; e; e = nxt[e])
        if (to[e] != ff) {
            dfs(to[e], u);
            if (len[to[e]] > len[son[u]])
                son[u] = to[e];
        }
    len[u] = len[son[u]] + 1;
}
void dp(int u, int ff) {
    f[u][0] = 1;
    if (son[u])
        f[son[u]] = f[u] + 1, dp(son[u], u), ans[u] = ans[son[u]] + 1;
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (v == ff || v == son[u])
            continue;
        f[v] = id;
        id += len[v];
        dp(v, u);
        for (int j = 1; j <= len[v]; ++j) {
            f[u][j] += f[v][j - 1];
            if ((j < ans[u] && f[u][j] >= f[u][ans[u]]) ||
                (j > ans[u] && f[u][j] > f[u][ans[u]]))
                ans[u] = j;
        }
    }
    if (f[u][ans[u]] == 1)
        ans[u] = 0;
}
int main() {
    n = gi();
    for (int i = 1; i < n; ++i)
        link(gi(), gi());
    dfs(1, 0);
    f[1] = id;
    id += len[1];
    dp(1, 0);
    for (int i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}