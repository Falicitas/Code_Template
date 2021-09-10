void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    sta[++top] = u,vis[u] = 1;
    UREP(i,u){
        int v = edge[i].v;
        if(!dfn[u]){
            tarjan(v);
            low[u] = min(low[u],low[v]);
        }
        else if(vis[v]) low[u] = min(low[u],dfn[v]);//忽略横插边的影响
    }
    if(dfn[u]==low[u]){
        cc++;int cur;
        do{
            cur = sta[top--],vis[cur] = 0;
            num[cur] = cc;
        }while(u!=cur);
    }
}
