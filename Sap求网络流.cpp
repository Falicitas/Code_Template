int dfs(int u,int flow)//int dfs返回从x出发，携带flow值能传到汇点t的最大流量
{
    if(u==t) return flow;//已经是汇点了直接返回flow
    int sum = 0;//指可以从x流出的最大流量总和
    UREP(i,u){
        int v = edge[i].v;
        if(edge[i].c&&d[u]==d[v]+1){//往最短路走
            int v = edge[i].v,tmp = dfs(v,min(edge[i].c,flow-sum));//flow-sum指剩余可流流量
            edge[i].c -= tmp,edge[i^1].c += tmp;
            sum += tmp;
            if(sum==flow) return sum;//可用流量已用完
        }
    }
    if(d[S]>=n+3) return sum;//已出现断层，此时直接返回

    cntd[d[u]]--;//cntd指x所在层同层有多少个节点
    if(!cntd[d[u]]) d[S] = n + 3;//如果出现断层，此时不可能再有贡献。同时让其他的递归完成后再结束程序，至少保证増广路成功回溯完毕
    d[u]++;
    cntd[d[u]]++;
    return sum;
}

void init()
{
    cntd[0] = n;
}
