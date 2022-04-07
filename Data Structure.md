[toc]

# 动态树

```cpp
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 100010;

int n, m;
struct Node {
    int s[2], p, v;
    int sum, rev;
} tr[N];
int stk[N];

void pushrev(int x) {
    swap(tr[x].s[0], tr[x].s[1]);
    tr[x].rev ^= 1;
}

void pushup(int x) {
    tr[x].sum = tr[tr[x].s[0]].sum ^ tr[x].v ^ tr[tr[x].s[1]].sum;
}

void pushdown(int x) {
    if (tr[x].rev) {
        pushrev(tr[x].s[0]), pushrev(tr[x].s[1]);
        tr[x].rev = 0;
    }
}

bool isroot(int x) {  //是否为splay树中的根
    return tr[tr[x].p].s[0] != x && tr[tr[x].p].s[1] != x;
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    if (!isroot(y))
        tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x) {
    int top = 0, r = x;
    stk[++top] = r;
    while (!isroot(r))
        stk[++top] = r = tr[r].p;
    while (top)
        pushdown(stk[top--]);  //把x到根的所有lazy-tag放完
    while (!isroot(x)) {
        int y = tr[x].p, z = tr[y].p;
        if (!isroot(y))
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y))
                rotate(x);
            else
                rotate(y);
        rotate(x);
    }
}

void access(int x)  // 建立一条从根到x的路径，同时将x变成splay的根节点
{
    int z = x;
    for (int y = 0; x; y = x, x = tr[x].p) {
        splay(x);
        tr[x].s[1] = y, pushup(x);
    }
    splay(z);
}

void makeroot(int x)  // 将x变成原树的根节点
{
    access(x);
    pushrev(x);
}

int findroot(int x)  // 找到x所在原树的根节点, 再将原树的根节点旋转到splay的根节点
{
    access(x);
    while (tr[x].s[0])
        pushdown(x), x = tr[x].s[0];
    splay(x);
    return x;
}

void split(int x, int y)  // 给x和y之间的路径建立一个splay，其根节点是y
{
    makeroot(x);
    access(y);
}

void link(int x, int y)  // 如果x和y不连通，则加入一条x和y之间的边
{
    makeroot(x);
    if (findroot(y) != x)
        tr[x].p = y;
}

void cut(int x, int y)  // 如果x和y之间存在边，则删除该边
{
    makeroot(x);
    if (findroot(y) == x && tr[y].p == x && !tr[y].s[0]) {
        tr[x].s[1] = tr[y].p = 0;
        pushup(x);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &tr[i].v);
    while (m--) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        if (t == 0) {
            split(x, y);
            printf("%d\n", tr[y].sum);
        } else if (t == 1)
            link(x, y);
        else if (t == 2)
            cut(x, y);
        else {
            splay(x);
            tr[x].v = y;
            pushup(x);
        }
    }
    return 0;
}
```

# 回滚莫队（不删除莫队）

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using i64 = long long;

//举例：维护区间相同数出现次数最多的次数（不删回滚莫队，x范围1~n）
struct BackMo {
    BackMo() {
        int n, q;
        cin >> n >> q;
        vector<int> x(n + 1), cnt(n + 1);

        vector<tuple<int, int, int>> Q(q);  // l,r,id
        vector<int> ans(q);

        for (int i = 1; i <= n; i++)
            cin >> x[i];
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            Q[i] = make_tuple(l, r, i);
        }

        vector<int> pos(n + 1), L(n + 1), R(n + 1);
        int sz, tot;
        auto build = [&] {
            sz = max(n / sqrt(q), 1.0);
            tot = n / sz;
            for (int i = 1; i <= tot; i++) {
                L[i] = (i - 1) * sz + 1;
                R[i] = i * sz;
            }
            if (R[tot] < n) {
                ++tot;
                L[tot] = R[tot - 1] + 1;
                R[tot] = n;
            }
        };

        build();

        // 对询问进行排序
        for (int i = 1; i <= tot; i++)
            for (int j = L[i]; j <= R[i]; j++)
                pos[j] = i;
        sort(Q.begin(), Q.end(), [&](tuple<int, int, int> x, tuple<int, int, int> y) {
            if (pos[get<0>(x)] == pos[get<0>(y)]) {
                return get<1>(x) < get<1>(y);
            }
            return pos[get<0>(x)] <= pos[get<0>(y)];
        });

        int l = 1, r = 0, last_block = 0, __l;

        auto Add = [&](int v, int& res) {
            //在Add时可能是负区间的，此时ignore。Del同理
            if (r - l + 1 >= 0) {
                cnt[v]++;
                // 信息维护
                res = max(res, cnt[v]);
                // 答案统计
            }
        };

        auto Del = [&](int v) {
            if (r - l + 1 >= 1) {
                cnt[v]--;
                // 信息维护
            }
        };

        int Ans = 0, tmp = 0;
        for (int i = 0; i < q; i++) {
            auto [ql, qr, id] = Q[i];
            // 询问的左右端点同属于一个块则暴力扫描回答
            if (pos[ql] == pos[qr]) {
                tmp = 0;
                for (int j = ql; j <= qr; j++) {
                    //处理答案
                }
                ans[id] = tmp;
                continue;
            }

            if (pos[ql] != last_block) {
                while (r > R[pos[ql]]) {
                    Del(x[r]);
                    r--;
                }
                while (l < R[pos[ql]] + 1) {
                    Del(x[l]);
                    l++;
                }
                Ans = 0;  //不同块清空答案
                last_block = pos[ql];
            }

            // 扩展右端点
            while (r < qr) {
                ++r;
                Add(x[r], Ans);
            }
            __l = l;
            tmp = Ans;  // 保留未扩展左指针的答案，以免对答案产生影响，避免写可撤销数据结构

            // 扩展左端点
            while (__l > ql)
                --__l, Add(x[__l], tmp);
            ans[id] = tmp;

            // 回滚
            while (__l < l)
                Del(x[__l]), ++__l;
        }
        for (int i = 0; i < q; i++) {
            cout << ans[i] << "\n";
        }
    }
};
```

# 可持久化线段树

基于线段树的基础数据结构，通过动态开点维护新的版本信息，同时与上个版本不变的数据块相连，充分利用空间。每个版本的根节点代表的都是完整的一颗线段树。

## 可持久化数组

维护 $a_1,a_2,...,a_n$，支持历史版本的单点修改与单点查询。

```cpp
// code sourced from kinesis
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
struct node {
    int v, ls, rs;
} e[N * 23];
int his[N], cnt = 0;
#define v(p) e[p].v
#define ls(p) e[p].ls
#define rs(p) e[p].rs
int bld(int l, int r)  //这里的l,r是区间
{
    int p = ++cnt;
    if (l == r)
        cin >> v(p);
    if (l < r) {
        int mid = l + r >> 1;
        ls(p) = bld(l, mid);
        rs(p) = bld(mid + 1, r);
    }
    return p;
}
int update(int pre, int l, int r, int x, int v, int op) {
    int p = ++cnt;
    e[p] = e[pre];
    if (op == 2)
        return p;
    if (l == r)
        v(p) = v;
    if (l < r) {
        int mid = l + r >> 1;
        if (x <= mid)
            ls(p) = update(ls(pre), l, mid, x, v, op);
        else
            rs(p) = update(rs(pre), mid + 1, r, x, v, op);
    }
    return p;
}
int query(int id, int l, int r, int k) {
    if (l == r)
        return v(id);  //返回id版本在位置k的值
    int mid = l + r >> 1;
    if (k <= mid)
        return query(ls(id), l, mid, k);
    else
        return query(rs(id), mid + 1, r, k);
}

int main() {  // ONLINE_JUDGE
    int n, m;
    cin >> n >> m;
    his[0] = bld(1, n);
    for (int i = 1; i <= m; i++) {
        int id, op, idx, val;
        cin >> id >> op >> idx;
        if (op == 1)
            cin >> val;
        else
            cout << query(his[id], 1, n, idx) << "\n";
        his[i] = update(his[id], 1, n, idx, val, op);
    }
    return 0;
}

```

## 可持久化值域线段树 & 可持久化并查集（线性基）

可持久化线段树的一类应用。由于某值域内元素的个数具有可减性，故可以用可持久化线段树的两个版本进行相减，以达到查询区间第 k 大，区间小于某数的元素个数（进一步理解，则是相当于维护了任意区间的有序数列，一切对有序数列的更快复杂度的信息统计，在可持久化值域线段树内也可以做到）

可持久化并查集和线性基用可持久化数组即可维护。只不过底层维护的值不同而已。

## 一些题目

### P4137 Rmq Problem / mex

求区间mex的应用。mex是区间 $[l,r]$ 中没有出现的最小的自然数，只需要在值域上维护 $[1,r]$ 上某个值的最右下标，查询时找 $[1,r]$ 中比 $l$ 小的最小的值就行。

# 李超线段树 & 楼房重建问题

要求在平面直角坐标系下维护两个操作（强制在线）：

> 1. 在平面上加入一条线段。记第 $i$ 条被插入的线段的标号为 $i$，该线段的两个端点分别为 $(x_0,y_0)$，$(x_1,y_1)$。
> 2. 给定一个数 $k$，询问与直线 $x = k$ 相交的线段中，交点纵坐标最大的线段的编号（若有多条线段与查询直线的交点纵坐标都是最大的，则输出编号最小的线段）。特别地，若不存在线段与给定直线相交，输出 $0$。
>
> 数据满足：操作总数 $1 \leq n \leq 10^5$，$1 \leq k, x_0, x_1 \leq 39989$，$1 \leq y_0, y_1 \leq 10^9$。

我们发现，传统的线段树无法很好地维护这样的信息。这种情况下，**李超线段树** 便应运而生。

## 概述

我们设法维护每个区间中，可能成为最优解的线段。

称一条线段在 $x=x_0$ 处最优，当且仅当该线段在 $x_0$ 处取值最大。

称一条线段能成为区间 $[l,r]$ 中的 **最优线段**，当且仅当：

1. 该线段的定义域完整覆盖了区间 $[l,r]$；
2. 该线段在区间中点处最优。

现在我们需要插入一条线段 $f$，在这条线段完整覆盖的区间中，某些区间的最优线段可能发生改变。

考虑某个被新线段 $f$ 完整覆盖的区间，若该区间无最优线段，则该线段可以直接成为最优线段。

否则，设该区间的中点为 $m$，我们拿新线段 $f$ 在中点处的值与原最优线段 $g$ 在中点处的值作比较。

首先，如果新线段 $f$ 斜率大于原线段 $g$，

1. 如果 $f$ 在 $m$ 处更优，则 $f$ 在右半区间 **一定** 最优，$g$ 在左半区间 **可能** 最优；

![image-20211105173716186](https://raw.githubusercontent.com/Falicitas/Image-Hosting/main/image-20211105173716186.png)

2. 反之，$g$ 在左半区间 **一定** 最优，$f$ 在右半区间 **可能** 最优。

![image-20211105173742888](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20211105173742888.png)

接下来考虑 $f$ 斜率小于 $g$ 的情况，

1. 如果 $f$ 在 $m$ 处更优，则 $f$ 在左半区间 **一定** 最优，$g$ 在右半区间 **可能** 最优；

![image-20211105173803035](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20211105173803035.png)

2. 反之，$g$ 在右半区间 **一定** 最优，$f$ 在左半区间 **可能** 最优。

![image-20211105173841351](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20211105173841351.png)

最后考虑新线段和旧线段斜率相同的情况，此时只需比较截距即可，截距大的一定在整个区间内更优。

确定完当前区间的最优线段后，我们需要递归进入子区间，更新最优线段可能改变的区间。

这样的过程与一般线段树的递归过程类似，因此我们可以使用线段树来维护。

现在考虑如何查询一个区间的最优线段。

查询过程利用了标记永久化的思想，简单地说，我们将所有包含 $x_0$ 区间（易知这样的区间只有 $O(\log n)$ 个）的最优线段拿出来，在这些线段中比较，从而得出最优线段。

根据上面的描述，查询过程的时间复杂度显然为 $O(\log n)$，而插入过程中，我们需要将原线段分割到 $O(\log n)$ 个区间中，对于每个区间，我们又需要花费 $O(\log n)$ 的时间更新该区间以及其子区间的最优线段，从而插入过程的时间复杂度为 $O(\log^2 n)$。

## 代码

参见「P4069 [SDOI2016]游戏」。

## 楼房重建

能看到楼 i 当且仅当楼 i 的斜率为严格的前缀最大值。

考虑线段树。维护两个值 $id,cnt$，定义为当前节点 p 的最大斜率的位置，和仅考虑当前区间的影响时右区间的答案。即已经在有左区间的前缀的前提下，右区间有多少个 i 满足楼 i 的斜率为严格的前缀最大值。

设计`int cal(p,pre)`为对于当前节点 $p$，有前缀最大值 pre 时，$p$ 位置的贡献：

当 pre 小于当前节点左区间，说明 pre 对当前右区间的答案计算无影响，返回 `cal(ls,pre)+cnt[p]`

否则左区间答案无贡献，返回 `cal(rs,pre)`。

这里补充一点，`cal(p,pre)`函数相当于向上维护的过程，即当左右区间都维护好时开始统计的，故此时不用担心维护左右区间时的答案贡献正确性。

```cpp
// code sourced from kinesis
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5, inf = 0x3f3f3f3f;

int id[N << 2], cnt[N << 2], H[N];

bool pt(int p1, int p2) {
    if (!p2)
        return H[p1];
    return 1LL * H[p1] * p2 > 1LL * H[p2] * p1;
}

#define lp (p << 1)
#define rp (p << 1 | 1)
#define mid (l + r >> 1)
#define ls lp, l, mid
#define rs rp, mid + 1, r

void bld(int p, int l, int r) {
    id[p] = l, cnt[p] = 0;  //这里的cnt[p]可以取任何值，因为其并无定义
    if (l == r)
        return;
    // int mid = l + r >> 1;
    bld(ls), bld(rs);
}

int calc(int p, int l, int r, int pre) {
    if (l == r)
        return pt(l, pre);
    if (pt(id[lp], pre))
        return calc(ls, pre) + cnt[p];
    else
        return 0 + calc(rs, pre);
}

void chg(int p, int l, int r, int x, int y) {
    if (l == r)
        return (void)(H[x] = y);
    if (x <= mid)
        chg(ls, x, y);
    else
        chg(rs, x, y);
    id[p] = pt(id[rp], id[lp]) ? id[rp] : id[lp];
    cnt[p] = calc(rs, id[lp]);
}

int main() {
    int n, m;
    cin >> n >> m;
    bld(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        chg(1, 1, n, x, y);
        cout << calc(1, 1, n, 0) << "\n";
    }
    return 0;
}

```

## 一些习题

### P4069 [SDOI2016]游戏

游戏在一棵有 $n$ 个点的树上进行。最初，每个点上都只有一个数字，那个数字是 123456789123456789。

有时， Alice 会选择一条从 $s$ 到 $t$ 的路径，在这条路径上的每一个点上都添加一个数字。对于路径上的一个 点 $r$，若 $r$ 与 $s$ 的距离是 $d i s$，那么 Alice 在点 $r$ 上添加的数字是 $a \times d i s+b$。
有时，Bob 会选择一条从 $s$ 到 $t$ 的路径。他需要先从这条路径上选择一个点，再从那个点上选择一个数字。

Bob 选择的数字越小越好，但大量的数字让 Bob 眼花缭乱。Bob 需要你帮他找出他能够选择的最小的数字。

由 $a \times d i s+b$ 可以看出这个东西是个一次函数。

然后你就会发现这个东西可以用永久化标记的李超线段树做。

- 仔细分析这个式子：

$$
a n s=\max \{a \times(\operatorname{dis}[i]-d i s[s])+b\} \quad i \in\{s, \cdots t\}
$$

然后把它优雅地拆开，令 $x=l c a(s, t)$。

- 那么 $s$ 到 $x$ 就可以表示为这么一条直线:

$$
y=-a \times \operatorname{dis}[i]+(a \times \operatorname{dis}[s]+b) \quad i \in\{s, \cdots x\}
$$

- $t$ 到 $x$ 同理为:

$$
y=a \times d i s[i]+a \times(d i s[s]-2 \times d i s[x]) \quad i \in\{s, \cdots x\}
$$

于是直接上李超线段树，用树链剖分维护树上的 $i d[i]$，并对线段树里记录一个原始编号 $b e l[i d[i]]=i$，每次的 $dis[i]$ 就可以求了。

示例代码：

```cpp
// code sourced from kinesis
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
constexpr i64 inf = 123456789123456789;
const int maxn = 1e5 + 5, maxm = 2e5 + 5;
struct E {
    int v, next;
    i64 w;
} edge[maxm];
int p[maxn], eid;
void init_E() {
    memset(p, -1, sizeof p), eid = 0;
}
void link1(int u, int v, i64 w) {
    edge[eid].v = v, edge[eid].w = w, edge[eid].next = p[u], p[u] = eid++;
}
void link2(int u, int v, i64 w) {
    link1(u, v, w), link1(v, u, w);
}

int dfn[maxn], rnk[maxn], tp[maxn], siz[maxn], fa[maxn], bson[maxn], newid, rt,
    cnt;
i64 d[maxn], k[maxn << 1], b[maxn << 1];

void dfs1(int u) {
    bson[u] = -1;
    siz[u] = 1;
    for (int i = p[u]; i + 1; i = edge[i].next) {
        int v = edge[i].v;
        if (v == fa[u])
            continue;
        d[v] = d[u] + edge[i].w;
        fa[v] = u;
        dfs1(v);
        siz[u] += siz[v];
        if (bson[u] == -1 || siz[v] > siz[bson[u]])
            bson[u] = v;
    }
}

void dfs2(int u, int top) {
    dfn[u] = ++cnt;
    rnk[cnt] = u;
    tp[u] = top;
    if (bson[u] == -1)
        return;
    dfs2(bson[u], top);
    for (int i = p[u]; i + 1; i = edge[i].next) {
        int v = edge[i].v;
        if (v == fa[u] || v == bson[u])
            continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (tp[u] != tp[v]) {
        if (d[tp[u]] < d[tp[v]])
            swap(u, v);
        u = fa[tp[u]];
    }
    if (d[u] > d[v])
        swap(u, v);
    return u;
}

#define lp (p << 1)
#define rp (p << 1 | 1)
#define mid (l + r >> 1)
#define ls lp, l, mid
#define rs rp, mid + 1, r

i64 mn[maxn << 2];
int t[maxn << 2];
int n;

void bld(int p, int l, int r) {
    mn[p] = inf;
    if (l == r)
        return;
    bld(ls), bld(rs);
}

i64 cal(int l, int id) {
    return k[id] * d[rnk[l]] + b[id];
}

void chkmin(i64& u, i64 v) {
    if (v < u)
        u = v;
}

void chg(int p, int l, int r, int cl, int cr, int id) {
    if (cl <= l && r <= cr) {
        if (cal(l, id) <= cal(l, t[p]) && cal(r, id) <= cal(r, t[p])) {
            t[p] = id;
            chkmin(mn[p], min(cal(l, id), cal(r, id)));
            return;
        }
        if (cal(l, id) >= cal(l, t[p]) && cal(r, id) >= cal(r, t[p]))
            return;  // for leaf node,either ended in here or in front code
        chkmin(mn[p], min(cal(l, id), cal(r, id)));//维护这一段的最小值
        if (cal(mid, id) <= cal(mid, t[p]))
            swap(t[p], id);
        if (cal(l, id) <= cal(l, t[p]))
            chg(ls, cl, cr, id);
        if (cal(r, id) <= cal(r, t[p]))
            chg(rs, cl, cr, id);
        return;
    }
    if (cl <= mid)
        chg(ls, cl, cr, id);
    if (cr > mid)
        chg(rs, cl, cr, id);
    chkmin(mn[p], min(mn[lp], mn[rp]));
}

i64 query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return mn[p];
    i64 res = inf;
    if (t[p])
        res = min(cal(max(l, ql), t[p]), cal(min(r, qr), t[p]));
    if (ql <= mid)
        chkmin(res, query(ls, ql, qr));
    if (qr > mid)
        chkmin(res, query(rs, ql, qr));
    return res;
}

void modify(int u, int v, int line_id) {
    while (tp[u] != tp[v]) {
        if (d[tp[u]] < d[tp[v]])
            swap(u, v);
        chg(1, 1, n, dfn[tp[u]], dfn[u], line_id);
        u = fa[tp[u]];
    }
    if (d[u] > d[v])
        swap(u, v);
    chg(1, 1, n, dfn[u], dfn[v], line_id);
}

i64 mx(int u, int v) {
    i64 res = inf;
    while (tp[u] != tp[v]) {
        if (d[tp[u]] < d[tp[v]])
            swap(u, v);
        chkmin(res, query(1, 1, n, dfn[tp[u]], dfn[u]));
        u = fa[tp[u]];
    }
    if (d[u] > d[v])
        swap(u, v);
    chkmin(res, query(1, 1, n, dfn[u], dfn[v]));
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
// freopen("in.txt","r",stdin);//cf,atcoder,nowcoder needn't delete this
#endif  // ONLINE_JUDGE
    int m;
    cin >> n >> m;
    init_E();
    for (int i = 1; i < n; i++) {
        int u, v;
        i64 w;
        cin >> u >> v >> w;
        link2(u, v, w);
    }
    rt = rand() % n + 1;
    dfs1(rt), dfs2(rt, rt);
    b[0] = inf;
    bld(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int u, v, K, B;
            cin >> u >> v >> K >> B;
            int w = lca(u, v);
            newid++;
            k[newid] = -K, b[newid] = 1LL * K * d[u] + B;
            modify(u, w, newid);
            newid++;
            k[newid] = K, b[newid] = 1LL * K * (d[u] - 2 * d[w]) + B;
            modify(v, w, newid);
        } else {
            int u, v;
            cin >> u >> v;
            mx(u, v);
        }
    }
    return 0;
}
```

# 线性基

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = int;

struct Linear_base {
    vector<u64> lb;
    Linear_base() {
        lb = vector<u64>(27);
    }
    void insert(u64 x) {
        for (int i = 26; i >= 0; i--) {
            if (x & (1ull << i)) {
                if (!lb[i]) {
                    lb[i] = x;
                    return;
                } else {
                    x ^= lb[i];
                }
            }
        }
    }
    bool check(u64 x) {  //查看是否存在在一个子集，使异或和为x
        for (int i = 26; i >= 0; i--) {
            if (x & (1ull << i)) {
                if (!lb[i]) {
                    return false;
                } else {
                    x ^= lb[i];
                }
            }
        }
        return true;
    }
    u64 qmax() {
        u64 res = 0;
        for (int i = 26; i >= 0; i--) {
            res = max(res, res ^ lb[i]);
        }
        return res;
    }
    u64 qmin() {
        for (int i = 0; i <= 26; i++) {
            if (lb[i]) {
                return lb[i];
            }
        }
    }

    //剩个找第k大
};

// 线性基合并过程
// Basis tmp = T[rt << 1], v1 = T[rt << 1], v2 = T[rt << 1 | 1];
// for (LL i = 0; i < 32; i++) {
//     if (v2.basis[i]) {
//         bool flag = true;
//         LL x = v2.basis[i], now = 0;
//         for (LL j = 31; j >= 0; j--) {
//             if (x & (1ll << j)) {
//                 if (!tmp.basis[j]) {
//                     flag = false;
//                     tmp.basis[j] = x;
//                     v1.basis[j] = now;
//                     break;
//                 }
//                 x ^= tmp.basis[j];
//                 now ^= v1.basis[j];
//             }
//         }
//         if (flag)
//             T[rt].Update(now);
//     }
// }

```

# FHQ-treap

```cpp
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
//放一些基本的函数
int rnd() {
    static int seed = 233;
    return seed = (int)seed * 482711LL % 2147483647;
}

constexpr int N = 1e6 + 5;
int root, pool[N], eid, r1, r2, r3;  // ri是待用的分裂根节点

struct node {
    int fa, ch[2], siz, key;
    i64 val, tag;
    void clear() {
        fa = ch[0] = ch[1] = siz = val = key = tag = 0;
    }
} T[N];

void del(int x) {
    if (!x)
        return;
    T[x].clear(), pool[--eid] = x;
}
int nw() {
    return pool[eid++];
}

void init() {  //记得初始化
    for (int i = 1; i < N; i++)
        pool[i] = i;
    eid = 1;
}

void up(int now) {
    if (!now)
        return;
    T[now].siz = 1;
    if (T[now].fa && T[T[now].fa].ch[0] != now && T[T[now].fa].ch[1] != now)
        T[now].fa = 0;  //在split时可能now节点会作为根节点
    if (T[now].ch[0])
        T[now].siz += T[T[now].ch[0]].siz, T[T[now].ch[0]].fa = now;
    if (T[now].ch[1])
        T[now].siz += T[T[now].ch[1]].siz, T[T[now].ch[1]].fa = now;
}

void do_sth(int now, int tag) {
    if (!now)
        return;
    //对于当前点now的维护值改变
    // now的懒标记进行修改
    //有必要时清空当前点的其它懒标记
}

void down(int now) {
    if (!now)
        return;
    if (T[now].tag) {
        if (T[now].ch[0])
            do_sth(T[now].ch[0], T[now].tag);  //各种操作
        if (T[now].ch[1])
            do_sth(T[now].ch[1], T[now].tag);  //各种操作
        T[now].tag = 0;                        //懒标记已下传
    }
}

int newnode(int x) {
    int u = nw();
    T[u].val = x, T[u].key = rnd(), T[u].siz = 1;
    return u;
}

void split(int now, int k, int& x, int& y)  //按排名分裂
{
    if (!now)
        return (void)(x = y = 0);
    down(now);
    if (T[T[now].ch[0]].siz >= k)
        y = now, split(T[now].ch[0], k, x, T[now].ch[0]);
    else
        x = now, split(T[now].ch[1], k - T[T[now].ch[0]].siz - 1, T[now].ch[1], y);
    up(now);
}

void split(int now, int k, int& x, int& y)  //按值分裂 [-inf,k],[k+1,inf]
{
    if (!now)
        return (void)(x = y = 0);
    down(now);
    if (T[now].val <= k)
        x = now, split(T[now].ch[1], k, T[now].ch[1], y);
    else
        y = now, split(T[now].ch[0], k, x, T[now].ch[0]);
    up(now);
}

int merge(int u, int v)  // u左区间树，v右区间树。调用merge记得给root赋值
{
    if (!u || !v)
        return u | v;
    if (T[u].key < T[v].key) {
        down(u);
        T[u].ch[1] = merge(T[u].ch[1], v);
        up(u);
        return u;
    } else {
        down(v);
        T[v].ch[0] = merge(u, T[v].ch[0]);
        up(v);
        return v;
    }
}

void myclear(int now) {  //在findsiz函数中最先调用
    if (now != root)
        myclear(T[now].fa);  //先回溯父亲节点
    down(now);               //再下传标记
}

int findsiz(int now)  //按排名分裂，回溯找某个节点的排名。有懒标记操作前记得myclear从上至下down
{
    if (!root)
        return 0;
    int res = T[now].siz - T[T[now].ch[1]].siz;
    while (now != root) {
        if (now == T[T[now].fa].ch[1])
            res += T[T[now].fa].siz - T[now].siz;
        now = T[now].fa;
    }
    return res;
}

int kth(int k)  //排名第k小的节点，从1开始。返回节点编号
{
    int now = root;
    while (true) {
        down(now);
        if (T[T[now].ch[0]].siz >= k)
            now = T[now].ch[0];
        else if (k == T[T[now].ch[0]].siz + 1)
            return now;
        else
            k -= T[T[now].ch[0]].siz + 1, now = T[now].ch[1];
    }
}

void insert(int x) {
    split(root, x, r1, r2);
    root = merge(merge(r1, newnode(x)), r2);
}

void erase(int x)  //删一个
{
    split(root, x, r1, r3);
    split(r1, x - 1, r1, r2);
    down(r2);
    root = merge(merge(r1, merge(T[r2].ch[0], T[r2].ch[1])), r3);
    del(r2);
}


```

# RMQ

```cpp
#include <bits/stdc++.h>
using namespace std;

struct RMQ {
    int n;
    vector<int> lg2;
    vector<vector<int>> dmax, dmin;
    RMQ(const vector<int>& A) {
        n = A.size();
        lg2 = vector<int>(n + 1);
        for (int i = 0; i <= n; i++) {
            lg2[i] = (i == 0 ? -1 : lg2[i >> 1] + 1);
        }
        dmax = vector<vector<int>>(lg2[n] + 1, vector<int>(n));
        dmin = dmax;
        /*以上是数组的初始化*/
        for (int i = 0; i < n; i++)
            dmin[0][i] = dmax[0][i] = A[i];
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                dmin[j][i] = min(dmin[j - 1][i], dmin[j - 1][i + (1 << (j - 1))]);
                dmax[j][i] = max(dmax[j - 1][i], dmax[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int query(int l, int r, bool op) {
        int k = lg2[r - l + 1];
        r = r - (1 << k) + 1;
        return op == 0 ? min(dmin[k][l], dmin[k][r]) : max(dmax[k][l], dmax[k][r]);
    }
    /*op为0 min，op为1 max*/
};

struct RMQ_2D {
    int n, m;
    vector<int> lg2;
    vector<vector<vector<vector<int>>>> f;
    RMQ_2D(const vector<vector<int>>& val) {
        n = val.size(), m = val[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                f[0][0][i][j] = val[i][j];
            }
        }
        lg2 = vector<int>(max(n, m) + 1);
        for (int i = 0; i <= max(n, m); i++) {
            lg2[i] = (i == 0 ? -1 : lg2[i >> 1] + 1);
        }
        f = vector(lg2[n] + 1, vector(lg2[m] + 1, vector(n, vector<int>(m))));  //C++17标准
        /*以上是数组的初始化*/
        for (int i = 0; i < n; i++) {
            for (int k2 = 1; (1 << k2) <= m; k2++) {
                for (int j = 0; j + (1 << k2) - 1 < m; j++) {
                    f[0][k2][i][j] = max(f[0][k2 - 1][i][j], f[0][k2 - 1][i][j + (1 << (k2 - 1))]);
                }
            }
        }
        for (int k1 = 1; (1 << k1) <= n; k1++) {
            for (int i = 0; i + (1 << k1) - 1 < n; i++) {
                for (int k2 = 0; (1 << k2) <= m; k2++) {
                    for (int j = 0; j + (1 << k2) - 1 < m; j++) {
                        f[k1][k2][i][j] = max(f[k1 - 1][k2][i][j], f[k1 - 1][k2][i + (1 << (k1 - 1))][j]);
                    }
                }
            }
        }
    }
    int Query(int x1, int x2, int y1, int y2) {
        int k1 = lg2[x2 - x1 + 1], k2 = lg2[y2 - y1 + 1];
        x2 = x2 - (1 << k1) + 1, y2 = y2 - (1 << k2) + 1;
        return max(max(f[k1][k2][x1][y1], f[k1][k2][x2][y1]), max(f[k1][k2][x1][y2], f[k1][k2][x2][y2]));
    }
};
```

# rope、tree 及可持久化应用

rope 的底层是平衡树。支持以下操作：

| 函数           | 功能             |
| -------------- | ---------------- |
| push_back(x)   | 在末尾添加x      |
| insert(pos,x)  | 在pos插入x       |
| erase(pos,x)   | 从pos开始删除x个 |
| replace(pos,x) | 从pos开始换成x   |
| substr(pos,x)  | 提取pos开始x个   |
| at(x)/[x]      | 访问第x个元素    |

需要引入头文件和命名空间：

```cpp
#include <ext/rope>
using namespace __gnu_cxx;
```

上述的 pos 是光标，插入 x 指在 pos 前插入。故 pos 的范围在 $[0,rope.size]$​​​。rope 下标从 0 开始。

tree 的底层也是平衡树。

（以一道题为例）引入头文件：

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
```

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using i64 = long long;
using pii = pair<int, int>;

tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> t;  //会去重的红黑树

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        t.insert({x, i});
    }
    for (int i = n; i < n + m; i++) {
        int op, x;
        cin >> op >> x;
        if (op == 1)
            t.insert({x, i});  //插入x，用独特的<x,i>标注
        if (op == 2)
            t.erase(t.lower_bound({x, 0}));  //删除x（删除单个元素）
        if (op == 3)
            cout << t.order_of_key({x, 0}) + 1 << endl;  //x的排名（order_of_key = 小于x的元素个数，然后+1）
        if (op == 4)
            cout << t.find_by_order(x - 1)->first << endl;  //排名为x的元素（第x小）
        if (op == 5)
            cout << prev(t.lower_bound({x, 0}))->first << endl;  //x的前驱（小于x且最大）
        if (op == 6)
            cout << t.lower_bound({x + 1, 0})->first << endl;  //x的后继（大于x且最小）
    }
    return 0;
}
```

## 可持久化应用

rope 数据间拷贝仅拷贝根节点，所以是 $O(1)$​ 的。只需要调用下面的开辟空间命令就可实现可持久化：

```cpp
rope<char>*a,*b;
a=new rope<char>;
b=new rope<char>(*a);//O(1)拷贝
```

实测使用 tree 来可持久化比 rope 慢不少。对于按权值排序的平衡树，使用 rope 时维护一个有序数列即可。

# 可修莫队算法

```cpp
void add(int x) {
    cnt[x]++;
    if (cnt[x] == 1)
        ans++;
}

void del(int x) {
    cnt[x]--;
    if (cnt[x] == 0)
        ans--;
}

void add(int l, int r, int t)  //chg_idx为t时刻修改节点chg_idx[t]，前后的颜色为pre[t],cur[t]
{
    if (l <= chg_idx[t] && chg_idx[t] <= r) {
        cnt[pre[t]]--;
        if (!cnt[pre[t]])
            ans--;
        if (!cnt[cur[t]])
            ans++;
        cnt[cur[t]]++;
    }
    a[chg_idx[t]] = cur[t];
}

void del(int l, int r, int t) {
    if (l <= chg_idx[t] && chg_idx[t] <= r) {
        cnt[cur[t]]--;
        if (!cnt[cur[t]])
            ans--;
        if (!cnt[pre[t]])
            ans++;
        cnt[pre[t]]++;
    }
    a[chg_idx[t]] = pre[t];
}

struct node {
    int l, r, time, id;
    bool operator<(const node& rhs) {
        if (l / S != rhs.l / S)
            return l / S < rhs.l / S;
        if (r / S != rhs.r / S)
            return r / S < rhs.r / S;
        return time < rhs.time;
    }  //奇偶性排序基本无优化
} q[maxn];

//在获取答案时：init l = r = t = 0。cnt初始视情况而定
while (t < q[i].time)
    add(l, r, ++t);
while (t > q[i].time)
    del(l, r, t--);
while (l > q[i].l)
    add(a[--l]);
while (r < q[i].r)
    add(a[++r]);
while (l < q[i].l)
    del(a[l++]);
while (r > q[i].r)
    del(a[r--]);

S = ceil(pow(n, 2.0 / 3));

```

