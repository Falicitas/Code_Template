const int maxn = 1e5 + 5;
int size[maxn],maxs[maxn],totsize,root,dis[maxn][30],f[maxn][30],dep[maxn];
bool mark[maxn];

void dfs1(int u,int fa)
{
    size[u] = 1,maxs[u] = 0;
    UREP(i,u){
        int v = edge[i].v;
        if(v!=fa&&!mark[v]){
            dfs1(v,u);
            size[u] += size[v];
            maxs[u] = max(maxs[u],size[v]);
        }
    }
    maxs[u] = max(maxs[u],totsize-size[u]);
    if(maxs[u]<maxs[root]) root = u;
}

void dfsinit(int u,int fa,int k,int d)
{
    dep[u]++;//the level of the heavy point
    dis[u][dep[u]] = d;
    f[u][dep[u]] = k;
    UREP(i,u){
        int v = edge[i].v;
        if(mark[v]) continue;
        dfsinit(v,u,k,d+1);
    }
}

void solve(int rt)
{
    mark[rt] = 1;
    dfsinit(rt,0,rt,0);
    int tnt = totsize;
    UREP(i,rt){
        int v = edge[i].v;
        if(mark[v]) continue;
        totsize = size[v] > size[rt] ? tnt - size[rt] : size[v];
        root = 0;
        dfs1(v,u);
        solve(root);
    }
}
