#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 2000010;
int tot = 1, last = 1;
struct Node {
    int len, fa;  // len表示endp集合中最长子串的长度。fa表示最短子串再去一个首字母到达的endp状态
    int pos;      // pos表示endp集合里所有子串的结束点。有多个结束点取最前。比如xyzxyz,下标从1开始,pos("xyz") = pos("yz") = 3
    int ch[26];
    void init() {
        len = fa = pos = 0;
        memset(ch, 0, sizeof ch);
    }
} node[N];

i64 f[N];                        // f[u]表示节点u的结束点个数，亦即endp集合里所有子串分别出现的次数
int h[N], e[N], ne[N], idx = 0;  //后缀指针的反向边，以1为根节点的树
void init() {                    //注意初始化
    while (tot >= 1) {
        h[tot] = -1;
        f[tot] = 0;
        node[tot--].init();
    }
    tot = last = 1;
    idx = 0;
}
void extend(int c, int i) {
    int p = last, np = last = ++tot;
    f[tot] = 1;
    node[np].len = node[p].len + 1, node[np].pos = i;
    for (; p && !node[p].ch[c]; p = node[p].fa)
        node[p].ch[c] = np;
    if (!p)
        node[np].fa = 1;
    else {
        int q = node[p].ch[c];
        if (node[q].len == node[p].len + 1)
            node[np].fa = q;
        else {
            int nq = ++tot;
            node[nq] = node[q], node[nq].len = node[p].len + 1;
            node[q].fa = node[np].fa = nq;
            for (; p && node[p].ch[c] == q; p = node[p].fa)
                node[p].ch[c] = nq;
        }
    }
}

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u) {  //后缀指针构建的树。u的endp由儿子的并+当前节点是否是原串的前缀
    for (int i = h[u]; ~i; i = ne[i]) {
        dfs(e[i]);
        f[u] += f[e[i]];
    }
}