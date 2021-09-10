namespace L_TD//f[u][]维护u到子树距离为1,2,3...的节点个数。具体看要维护什么，这里举例
{
    int fa[maxn],len[maxn],bson[maxn],*f[maxn],tmp[maxn],*id=tmp;
    void dfs(int u)
    {
        UREP(i,u){
            int v = edge[i].v;
            if (v==fa[u]) continue;
            fa[v] = u;
            dfs(v);
            if (len[v]>len[bson[u]]) bson[u] = v;
        }
        len[u]=len[bson[u]]+1;
    }
    void solve(int u){
        f[u][0]=1;
        if (bson[u]) f[bson[u]]=f[u]+1,solve(bson[u]),...//重儿子的深度信息转移,如ans[u]=ans[son[u]]+1;
        UREP(i,u){
            int v=edge[i].v;
            if (v==fa[u]||v==bson[u]) continue;
            f[v]=id;id+=len[v];solve(v);
            for (int j=1;j<=len[v];++j){
                f[u][j] += f[v][j-1];
                //if ((j<ans[u]&&f[u][j]>=f[u][ans[u]])||(j>ans[u]&&f[u][j]>f[u][ans[u]]))
                //    ans[u]=j;
            }//维护深度相关信息
        }
        //if (f[u][ans[u]]==1) ans[u]=0;
    }
}
