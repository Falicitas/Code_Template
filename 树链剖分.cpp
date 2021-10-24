#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

/*
使用时，修改Info()的初值，Info +，与线段树里的修改函数
*/

constexpr int inf = INT_MAX;
template <class Info,
          class Merge = std::plus<Info>>
struct SegmentTree {
    const int n;
    const Merge merge;
    std::vector<Info> info;
    vector<Info> tag;
    SegmentTree(int n)  //初始化数组
        : n(n), merge(Merge()), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
    void pull(int p) {
        info[p] = merge(info[2 * p], info[2 * p + 1]);
    }
    void down(int p) {
        if (tag[p].s) {
            info[2 * p] = tag[p];
            info[2 * p + 1] = tag[p];
            tag[2 * p] = tag[p];
            tag[2 * p + 1] = tag[p];
            tag[p] = 0;
        }
    }
    void modify(int p, int l, int r, int cl, int cr, const Info& v) {
        if (cl <= l && r <= cr) {
            info[p] = v;
            tag[p] = v;
            return;
        }
        down(p);
        int m = (l + r) / 2;
        if (cl <= m) {
            modify(2 * p, l, m, cl, cr, v);
        }
        if (cr > m) {
            modify(2 * p + 1, m + 1, r, cl, cr, v);
        }
        pull(p);
    }
    void modify(int cl, int cr, const Info& v) {  //这里的p是单点位置
        modify(1, 1, n, cl, cr, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l > y || r < x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        down(p);
        int m = (l + r) / 2;
        return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m + 1, r, x, y));
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 1, n, l, r);
    }
};

struct Info {
    int s;
    Info()
        : s(inf) {}
    Info(int s_)
        : s(s_) {}
};

Info operator+(const Info& a, const Info& b) {
    Info c;
    c = min(a.s, b.s);
    return c;
}

struct tree_decomposition {  //下标1~n
    vector<int> dep, size, bson, dfn, rnk, top, bot;
    vector<vector<int>> fa;
    vector<vector<int>> e;
    SegmentTree<Info> seg;
    int cnt;
    tree_decomposition(vector<vector<int>> e_, vector<Info> a_, int rt)
        : e(e_), seg((int)e.size() - 1) {
        int n = e.size();
        n--;
        cnt = 0;
        dep = vector<int>(n + 1),
        size = bson = dfn = rnk = top = bot = dep;
        fa = vector<vector<int>>(n + 1, vector<int>((log2(n + 1) + 2)));
        dfs1(rt);
        dfs2(rt, rt);
        for (int i = 1; i <= n; i++) {
            seg.modify(i, i, a_[rnk[i]]);
        }
    }
    void dfs1(int u) {
        for (int lev = 1; lev < fa[u].size(); lev++) {
            fa[u][lev] = fa[fa[u][lev - 1]][lev - 1];
        }
        size[u] = 1;
        bson[u] = -1;
        for (auto v : e[u]) {
            if (v == fa[u][0]) {
                continue;
            }
            dep[v] = dep[u] + 1;
            fa[v][0] = u;
            dfs1(v);
            if (bson[u] == -1 || size[bson[u]] < size[v]) {
                bson[u] = v;
            }
            size[u] += size[v];
        }
    }
    void dfs2(int u, int tp) {
        top[u] = tp;
        cnt++;
        dfn[u] = cnt;
        rnk[cnt] = u;
        if (bson[u] == -1) {
            bot[u] = cnt;
            return;
        }
        dfs2(bson[u], tp);
        for (auto v : e[u]) {
            if (v == fa[u][0] || v == bson[u]) {
                continue;
            }
            dfs2(v, v);
        }
        bot[u] = cnt;
    }
    Info Query(int u, int v)  //维护路径上的点的信息
    {
        Info res;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            res = res + seg.rangeQuery(dfn[top[u]], dfn[u]);  //线段树处理的区间为[dfn[top[u]],dfn[u]]
            u = fa[top[u]][0];                                //跳链
        }
        if (dep[u] > dep[v])
            swap(u, v);                              //深度小的是lca，dfn序更小
        res = res + seg.rangeQuery(dfn[u], dfn[v]);  //[dfn[u],dfn[v]]
        return res;
    }
    int jump(int u, int d) {
        int mx = fa[1].size();
        for (int i = mx - 1; i >= 0; i--) {
            if (d >= (1 << i)) {
                d -= (1 << i);
                u = fa[u][i];
            }
        }
        return u;
    }
    int lca(int u, int v)  //维护路径上的点的信息
    {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            u = fa[top[u]][0];
        }
        if (dep[u] > dep[v])
            swap(u, v);
        return u;
    }
    void Modify(int u, int v, int val)  //维护路径上的点的信息
    {
        Info res;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            seg.modify(dfn[top[u]], dfn[u], val);  //线段树处理的区间为[dfn[top[u]],dfn[u]]
            u = fa[top[u]][0];                     //跳链
        }
        if (dep[u] > dep[v])
            swap(u, v);                   //深度小的是lca，dfn序更小
        seg.modify(dfn[u], dfn[v], val);  //[dfn[u],dfn[v]]
    }
};