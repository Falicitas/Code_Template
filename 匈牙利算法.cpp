int dfs(int u)
{
    UREP(i,u){
        int v = edge[i].v;
        if(vis[v]) continue;//当前匹配时已经访问过了，再访问会形成环，不是増广路
        vis[v] = 1;
        if(!link[v]||dfs(link[v])){ //去让之前匹配v的点u'找其他的匹配
            link[v] = u;
            return 1;
        }
    }
    return 0;
}

void Hungary()
{
    for(int i=1;i<=n;i++){//枚举其中一个点集
        memset(vis,0,sizeof vis);//缺省当前另外点集均无访问过
        dfs(i);
    }
}
