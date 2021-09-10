namespace TD//Tree-Decomposition
{
    int fa[maxn],dep[maxn],size[maxn],bson[maxn],dfn[maxn],rnk[maxn],top[maxn],cnt;
    void dfs1(int u)
    {
        size[u] = 1;
        bson[u] = -1;
        UREP(i,u){
            int v = edge[i].v;
            if(v==fa[u]) continue;
            dep[v] = dep[u] + 1;
            fa[v] = u;
            dfs1(v);
            if(bson[u]==-1 || size[bson[u]] < size[v]) bson[u] = v;
            size[u] += size[v];
        }
    }
    void dfs2(int u,int tp)
    {
        top[u] = tp;
        cnt++;
        dfn[u] = cnt;
        rnk[cnt] = u;
        if(bson[u]==-1) return ;
        dfs2(bson[u],tp);
        UREP(i,u){
            int v = edge[i].v;
            if(v==fa[u] || v==bson[u]) continue;
            dfs2(v,v);
        }
    }
    int cal_path(int u,int v)//维护路径上的点的信息
    {
        ll res = 0;
        while(top[u] != top[v]){
            if(dep[top[u]]<dep[top[v]]) swap(u,v);
            ...//线段树处理的区间为[dfn[top[u]],dfn[u]]
            u = fa[top[u]];//跳链
        }
        if(dep[u]>dep[v]) swap(u,v);//深度小的是lca，dfn序更小
        ...//[dfn[u],dfn[v]]
        return ...;
    }
    //子树操作的很好写，多一个数组bot[]，维护子树覆盖的cnt末尾
    //lca也是基于跳链、、很好写
}
