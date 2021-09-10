const int maxn = 1e5 + 5;
int size[maxn],maxs[maxn],totsize,root;
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

void solve(int rt)
{
    mark[rt]=1;
　　/*
　　　　deal with ans
　　*/
    int tnt = totsize;
    UREP(i,rt){
        int v = edge[i].v;
        if(!mark[v]){
            totsize = (size[v]>size[rt] ? tnt - size[rt] : size[v]);
            root=0;
            dfs1(v,0);
            solve(root);
        }
    }
}

void intn()
{
    maxs[0] = inf;
    root = 0;
    totsize = n;
    dfs1(1,0);
    solve(root);
}
