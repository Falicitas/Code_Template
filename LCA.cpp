const int maxn = 1e5 + 5;
int lca_p[maxn][30],n,d[maxn];
void dfs(int u)
{
    UREP(i,u){
        int v = edge[i].v;
        if(d[v]==-1){
            d[v] = d[u] + 1;
            lca_p[v][0] = u;
            dfs(v);
        }
    }
}

void pre_LCA()
{
    for(int level=1;(1<<level)<=n;level++){
        REP(i,1,n){
            lca_p[i][level] = lca_p[lca_p[i][level-1]][level-1];
        }
    }
}

void init_lca(){mem(d,-1);d[1] = 0;dfs(1);pre_LCA();}

int lca(int x,int y)
{
    int i,j;
    //int dist = 0;
    if(d[x]<d[y]) swap(x,y);
    for(i=0;(1<<i)<=d[x];i++);i--;
    for(j=i;j>=0;j--){
        if(d[x]-(1<<j)>=d[y]){
            x = lca_p[x][j];
            //dist += 1<<j;
        }
    }
    //if(x==y) return dist;
    if(x==y) return x;
    for(j=i;j>=0;j--){
        if(lca_p[x][j]!=lca_p[y][j]){
            x = lca_p[x][j];
            y = lca_p[y][j];
            dist += 2<<j;
        }
    }
    return lca_p[x][0];
    //return dist + 2;
}
//when calculating two points distance in grafh which is edge-weighed, dist = dist[v] + dist[u] - 2 * dist[lca], that dist[] can be caled by dfs.
