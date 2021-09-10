//解决子树叠加的问题
void dfs1(int u,int fa)
{
    siz[u] = 1;
    UREP(i,u){
        int v = edge[i].v;
        if(v==fa) continue;
        dfs1(v,u);
        siz[u] += siz[v];
        if(!bson[u]||siz[v]>siz[bson[u]]) bson[u] = v;
    }
}

void update(int u,int fa,int val,int son)//update函数见仁见智。
{
    cnt[c[u]] += val;
    if(val>0&&cnt[c[u]]>=max_cnt){
        if(cnt[c[u]]>max_cnt) sum = 0,max_cnt = cnt[c[u]];
        sum += c[u];
    }
    UREP(i,u){
        int v = edge[i].v;
        if(v==fa||v==son) continue;
        update(v,u,val,son);
    }
}

void dfs2(int u,int fa,int opt)
{
    UREP(i,u){
        int v = edge[i].v;
        if(v==fa||v==bson[u]) continue;
        dfs2(v,u,0);
    }
    if(bson[u]) dfs2(bson[u],u,1);
    update(u,fa,1,bson[u]);
    ans[u] = sum;
    if(!opt) update(u,fa,-1,0),sum = 0,max_cnt = 0;
}
