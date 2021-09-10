

//当场自敲一发更好。根据题目来敲


namespace dijkstra//叠加图
{
    int d[maxn],vis[maxn],n,m;
    struct Link
    {
        const static int maxn = 1e5 + 5,maxm = 2e5 + 5;
        struct E
        {
            int v,w,next;
        }edge[maxm];
        int p[maxn],eid;
        void init_E(){memset(p,-1,sizeof p),eid = 0;}
        void link1(int u,int v,int w){++eid,edge[eid].v = v,edge[eid].w = w,edge[eid].next = p[u],p[u] = eid;}
        void link2(int u,int v,int w){link1(u,v,w),link1(v,u,w);}
    }link;
    struct node
    {
        int v,d;
        node(int v=0,int d=0):v(v),d(d){}
        bool operator<(const node&rhs) const
        {
            return d > rhs.d;//don‘t click wrong !
        }
    };
    void dijk(int S)//non_negative value graph
    {
        REP(i,1,n) d[i] = inf;
        memset(vis,0,sizeof vis);
        d[S] = 0;
        priority_queue<node> pq;
        pq.push(node(S,0));
        while(!pq.empty()){
            node u = pq.top();pq.pop();
            if(vis[u.v]) continue;
            vis[u.v] = 1;
            for(int i=link.p[u.v];i+1;i=link.edge[i].next){
                int v = link.edge[i].v;
                if(!vis[v]&&d[u.v]+link.edge[i].w < d[v]){
                    d[v] = d[u.v] + link.edge[i].w;
                    pq.push(node(v,d[v]));
                }
            }
        }
    }
}

namespace dijkstra//常用
{
    struct E {int v,next,w;}edge[maxm];
    int p[maxn],eid;
    void init_E(){memset(p,-1,sizeof p),eid = 0;}
    void link1(int u,int v,int w){edge[eid].v = v,edge[eid].w = w,edge[eid].next = p[u],p[u] = eid++;}
    void link2(int u,int v,int w){link1(u,v,w),link1(v,u,w);}

    int d[maxn],vis[maxn],n;
    struct node
    {
        int v,d;
        node(int v=0,int d=0):v(v),d(d){}
        bool operator<(const node&rhs) const
        {
            return d > rhs.d;//don‘t click wrong !
        }
    };
    void dijk(int S)//non_negative value graph
    {
        REP(i,1,n) d[i] = inf;
        memset(vis,0,sizeof vis);
        d[S] = 0;
        priority_queue<node> pq;
        pq.push(node(S,0));
        while(!pq.empty()){
            node u = pq.top();pq.pop();
            if(vis[u.v]) continue;
            vis[u.v] = 1;
            UREP(i,u.v){
                int v = edge[i].v;
                if(!vis[v]&&d[u.v]+edge[i].w < d[v]){
                    d[v] = d[u.v] + edge[i].w;
                    pq.push(node(v,d[v]));
                }
            }
        }
    }
}

