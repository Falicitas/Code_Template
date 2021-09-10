int inq[maxn],d[maxn];
void spfa(int s)
{
    memset(inq,0,sizeof inq);
    REP(i,1,n) d[i] = inf;
    d[s] = 0;
    inq[s] = 1;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        inq[u] = 0;
        UREP(i,u){
            int v = edge[i].v;
            if(d[v]>d[u]+edge[i].v){
                d[v] = d[u] + edge[i].v;
                if(!inq[v]){
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
}
