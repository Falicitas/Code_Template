int dfs(int u)
{
    visx[u] = 1;
    for(int v=1;v<=m;v++){//m指m = max(n,m)
        if(!visy[v]&&lx[u]+ly[v]==w[u][v]){
            visy[v] = 1;
            if(link[v]==-1||dfs(link[v])){
                link[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

void KM()
{
    memset(ly,0,sizeof ly);
    memset(lx,0xf7,sizeof lx);//极小值
    memset(link,-1,sizeof link);
    REP(i,1,m) REP(j,1,m) lx[i] = max(w[i][j],lx[i]);
    REP(u,1,n){
        while(1){
            memset(visx,0,sizeof visx);
            memset(visy,0,sizeof visy);
            if(dfs(u)) break;
            int delt = inf;
            REP(j,1,n) if(visx[j]) REP(k,1,m) if(!visy[k]) delt = min(delt,lx[j]+ly[k]-w[j][k]);
            if(delt==inf) return -1;
            REP(i,1,n) if(visx[i]) lx[i] -= delt;
            REP(i,1,n) if(visy[i]) ly[i] += delt;
        }
    }
    /*因为最后是完美匹配，加上顶标就完事了
    int ans = 0;
    REP(i,1,n) ans += lx[i];
    REP(j,1,m) ans += ly[i];
    */
}
