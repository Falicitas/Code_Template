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
        res = res +
              seg.rangeQuery(dfn[top[u]],
                             dfn[u]);  //线段树处理的区间为[dfn[top[u]],dfn[u]]
        u = fa[top[u]][0];             //跳链
    }
    if (dep[u] > dep[v])
        swap(u, v);  //深度小的是lca，dfn序更小
    res = res + seg.rangeQuery(dfn[u], dfn[v]);  //[dfn[u],dfn[v]]
    return res;
}